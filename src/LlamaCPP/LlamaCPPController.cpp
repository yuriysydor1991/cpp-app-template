#include "src/LlamaCPP/LlamaCPPController.h"

#include <ggml-backend.h>
#include <llama.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <thread>

#include "src/LlamaCPP/ChatTemplate.h"
#include "src/log/log.h"

namespace llamacppi
{

namespace
{

/**
 * @brief Routes the llama.cpp and the ggml messages into the project logger.
 * A model load alone writes dozens of the info ones, so they go at the debug
 * level and the rest of the non failure ones at the trace level.
 */
void log_message(const ggml_log_level level, const char* const text,
                 [[maybe_unused]] void* const userData)
{
  std::string message{text != nullptr ? text : ""};

  if (!message.empty() && message.back() == '\n') {
    message.pop_back();
  }

  if (message.empty()) {
    return;
  }

  switch (level) {
    case GGML_LOG_LEVEL_ERROR:
      LOGE(message);
      break;
    case GGML_LOG_LEVEL_WARN:
      LOGW(message);
      break;
    case GGML_LOG_LEVEL_INFO:
      LOGD(message);
      break;
    default:
      LOGT(message);
  }
}

/**
 * @brief Hands the llama.cpp and the ggml messages over to the project logger
 * and loads the ggml backends, both once per process. A ggml built with the
 * dynamically loaded backends (the Debian packages one, for example) computes
 * nothing without them, while a statically linked one finds nothing to load.
 */
void prepare_llama()
{
  [[maybe_unused]] static const bool prepared = [] {
    llama_log_set(log_message, nullptr);
    ggml_backend_load_all();
    llama_backend_init();
    return true;
  }();
}

}  // namespace

bool LlamaCPPController::init(const std::string& modelPath)
{
  prepare_llama();

  // The context and the sampler of the loaded model go ahead of it.
  sampler.reset();
  context.reset();
  conversation.clear();
  evaluated.clear();

  model.reset(llama_model_load_from_file(modelPath.c_str(),
                                         llama_model_default_params()));

  if (model == nullptr) {
    LOGE("Fail to load the " << modelPath << " llama.cpp model");
    return false;
  }

  chatTemplate =
      ChatTemplate::create(llama_model_chat_template(model.get(), nullptr));

  if (chatTemplate == nullptr) {
    LOGE("No known chat template formats the conversation of the " << modelPath
                                                                   << " model");
    model.reset();
    return false;
  }

  auto params = llama_context_default_params();

  params.n_ctx =
      std::min(CONTEXT_SIZE,
               static_cast<uint32_t>(llama_model_n_ctx_train(model.get())));
  // The memory bandwidth limits the generation of the answer token by token,
  // so the half of the hardware threads generates it as fast as all of them,
  // while the evaluation of the prompt gains on every one.
  params.n_threads_batch =
      static_cast<int32_t>(std::max(1U, std::thread::hardware_concurrency()));
  params.n_threads = std::max(1, params.n_threads_batch / 2);
  // The cache of the sliding window attention keeps the last window of the
  // tokens alone instead of the whole context, which saves gigabytes for the
  // bigger models.
  params.swa_full = false;

  context.reset(llama_init_from_model(model.get(), params));

  if (context == nullptr) {
    LOGE("Fail to create the context of the " << modelPath
                                              << " llama.cpp model");
    model.reset();
    return false;
  }

  vocabulary = llama_model_get_vocab(model.get());

  sampler.reset(llama_sampler_chain_init(llama_sampler_chain_default_params()));

  llama_sampler_chain_add(sampler.get(), llama_sampler_init_top_k(TOP_K));
  llama_sampler_chain_add(sampler.get(), llama_sampler_init_top_p(TOP_P, 1U));
  llama_sampler_chain_add(sampler.get(), llama_sampler_init_min_p(MIN_P, 1U));
  llama_sampler_chain_add(sampler.get(), llama_sampler_init_temp(TEMPERATURE));
  llama_sampler_chain_add(sampler.get(),
                          llama_sampler_init_dist(LLAMA_DEFAULT_SEED));

  LOGD("The " << modelPath << " llama.cpp model is loaded with the context of "
              << llama_n_ctx(context.get()) << " tokens");

  return true;
}

LlamaCPPController::result LlamaCPPController::ask(const std::string& question,
                                                   const piece_handler& onPiece)
{
  if (context == nullptr) {
    LOGE("The llama.cpp controller is not initialized");
    return {};
  }

  conversation.emplace_back("user", question);

  const auto prompt = prompt_tokens();

  if (!prompt.has_value() || !evaluate(*prompt)) {
    conversation.pop_back();
    return {};
  }

  std::string answer;

  // The answer ends with the end of the generation token, by the handler or
  // once it fills the context up.
  while (evaluated.size() < llama_n_ctx(context.get())) {
    const llama_token token =
        llama_sampler_sample(sampler.get(), context.get(), -1);

    if (llama_vocab_is_eog(vocabulary, token)) {
      break;
    }

    const std::string piece = piece_of(token);

    answer += piece;

    if (onPiece && !onPiece(piece)) {
      break;
    }

    if (!decode({token})) {
      conversation.pop_back();
      return {};
    }
  }

  conversation.emplace_back("assistant", answer);

  return answer;
}

std::optional<LlamaCPPController::tokens> LlamaCPPController::prompt_tokens()
{
  const uint32_t size = llama_n_ctx(context.get());

  while (true) {
    const auto prompt = chatTemplate->apply(conversation);

    if (!prompt.has_value()) {
      LOGE("Fail to format the conversation with the model chat template");
      return {};
    }

    auto promptTokens = tokenize(*prompt);

    if (promptTokens.size() + (size / ANSWER_SHARE) <= size) {
      return promptTokens;
    }

    // The question being asked is the last message of the conversation.
    if (conversation.size() == 1U) {
      LOGE("The question of " << promptTokens.size()
                              << " tokens leaves too little room for the "
                                 "answer in the context of "
                              << size << " tokens");
      return {};
    }

    // The oldest question goes together with it's answer.
    conversation.erase(conversation.begin(), conversation.begin() + 2);
  }
}

bool LlamaCPPController::evaluate(const tokens& prompt)
{
  // The context keeps the tokens of the previous questions and answers, so the
  // evaluation goes on from the first prompt token differing from them, the
  // last prompt token at least, since it gives the logits of the answer.
  auto kept = static_cast<std::size_t>(
      std::mismatch(evaluated.cbegin(), evaluated.cend(), prompt.cbegin(),
                    prompt.cend())
          .first -
      evaluated.cbegin());

  kept = std::min(kept, prompt.size() - 1U);

  // The memory of the recurrent models drops no part of itself, while the
  // sliding window attention one keeps the last window of the tokens alone, so
  // the whole prompt is evaluated anew once the window ahead of the kept tokens
  // is gone.
  const llama_memory_t memory = llama_get_memory(context.get());
  const auto keptEnd = static_cast<llama_pos>(kept);

  if (!llama_memory_seq_rm(memory, 0, keptEnd, -1) ||
      llama_memory_seq_pos_min(memory, 0) >
          std::max(0, keptEnd - llama_model_n_swa(model.get()))) {
    llama_memory_clear(memory, true);
    kept = 0U;
  }

  evaluated.resize(kept);

  LOGD("Evaluating " << prompt.size() - kept << " of the " << prompt.size()
                     << " prompt tokens");

  return decode(
      {prompt.cbegin() + static_cast<std::ptrdiff_t>(kept), prompt.cend()});
}

bool LlamaCPPController::decode(tokens next)
{
  const auto batch = static_cast<std::ptrdiff_t>(llama_n_batch(context.get()));

  for (auto first = next.begin(); first != next.end();) {
    const auto last = first + std::min(batch, next.end() - first);

    if (llama_decode(context.get(),
                     llama_batch_get_one(
                         &*first, static_cast<int32_t>(last - first))) != 0) {
      LOGE("Fail to evaluate the " << last - first << " tokens");
      return false;
    }

    evaluated.insert(evaluated.end(), first, last);
    first = last;
  }

  return true;
}

LlamaCPPController::tokens LlamaCPPController::tokenize(
    const std::string& text) const
{
  tokens textTokens;
  int32_t count{0};

  // The first call tells the tokens count as a negative one.
  do {
    textTokens.resize(static_cast<std::size_t>(-count));
    count = llama_tokenize(vocabulary, text.data(),
                           static_cast<int32_t>(text.size()), textTokens.data(),
                           static_cast<int32_t>(textTokens.size()), true, true);
  } while (count < 0);

  return textTokens;
}

std::string LlamaCPPController::piece_of(const llama_token token) const
{
  std::string piece;
  int32_t length{0};

  // The first call tells the length as a negative one, while the control
  // tokens have no text to show.
  do {
    piece.resize(static_cast<std::size_t>(-length));
    length = llama_token_to_piece(vocabulary, token, piece.data(),
                                  static_cast<int32_t>(piece.size()), 0, false);
  } while (length < 0);

  return piece;
}

LlamaCPPControllerPtr LlamaCPPController::create()
{
  return std::make_shared<LlamaCPPController>();
}

}  // namespace llamacppi
