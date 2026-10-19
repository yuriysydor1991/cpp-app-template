#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LLAMACPPCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LLAMACPPCONTROLLER_CLASS_H

#include <llama.h>

#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "src/LlamaCPP/ChatTemplate.h"

/**
 * @brief The llama.cpp large language models adaptor subsystem namespace.
 */
namespace llamacppi
{

/**
 * @brief The llama.cpp chat controller. It loads a GGUF language model and
 * answers the questions of a conversation, handing every piece of the answer
 * over as soon as the model generates it.
 *
 * The model answers a question in the context of the previous questions and
 * answers, while the context of the model keeps their evaluated tokens, so the
 * next question evaluates it's own tokens alone. The oldest questions with
 * their answers get forgotten once the conversation outgrows the context. The
 * llama.cpp and the ggml messages go into the project logger. Nothing throws:
 * the failures are logged and reported through the return values.
 */
class LlamaCPPController
{
 public:
  using result = std::optional<std::string>;
  /// @brief Takes the next piece of the answer and tells whether the answer
  /// goes on, so a false value stops it.
  using piece_handler = std::function<bool(const std::string& piece)>;
  using LlamaCPPControllerPtr = std::shared_ptr<LlamaCPPController>;

  virtual ~LlamaCPPController() = default;
  LlamaCPPController() = default;
  LlamaCPPController(const LlamaCPPController&) = delete;
  LlamaCPPController& operator=(const LlamaCPPController&) = delete;

  /**
   * @brief Loads the model in place of the previously loaded one and starts a
   * new conversation.
   *
   * @param modelPath The GGUF model file path, e.g. the
   * models/gemma-4-E4B_q4_0-it.gguf one.
   *
   * @return Returns true on success and false if the model fails to load or
   * it's chat template is no known one.
   */
  virtual bool init(const std::string& modelPath);

  /**
   * @brief Asks the model the next question of the conversation.
   *
   * @param question The UTF-8 text of the question.
   * @param onPiece Takes the pieces of the answer one by one, while an empty
   * one leaves the whole answer to the return value.
   *
   * @return Returns the whole answer, the one stopped by the onPiece handler
   * included, or nothing if the controller is not initialized, the question
   * does not fit the context or the evaluation fails.
   */
  virtual result ask(const std::string& question, const piece_handler& onPiece);

  /**
   * @brief Creates a controller instance. Call the LlamaCPPController::init
   * method before the questions.
   *
   * @return The created controller.
   */
  static LlamaCPPControllerPtr create();

 private:
  using tokens = std::vector<llama_token>;

  /// @brief Formats and tokenizes the conversation, forgetting the oldest
  /// questions and answers while the prompt leaves too little room for the
  /// answer in the context.
  std::optional<tokens> prompt_tokens();

  /// @brief Evaluates the prompt tokens following the ones the context
  /// evaluated already.
  bool evaluate(const tokens& prompt);

  /// @brief Evaluates the given tokens next to the evaluated ones.
  bool decode(tokens next);

  tokens tokenize(const std::string& text) const;
  std::string piece_of(llama_token token) const;

  /// @brief The context the newer models are trained with takes gigabytes, so
  /// it is limited to this tokens count.
  inline static constexpr const uint32_t CONTEXT_SIZE = 8192U;

  /// @brief The share of the context the prompt leaves free for the answer:
  /// the quarter of it.
  inline static constexpr const uint32_t ANSWER_SHARE = 4U;

  /// @brief The sampling of the next token of the answer.
  inline static constexpr const int32_t TOP_K = 40;
  inline static constexpr const float TOP_P = 0.95F;
  inline static constexpr const float MIN_P = 0.05F;
  inline static constexpr const float TEMPERATURE = 0.8F;

  std::unique_ptr<llama_model, decltype(&llama_model_free)> model{
      nullptr, llama_model_free};
  std::unique_ptr<llama_context, decltype(&llama_free)> context{nullptr,
                                                                llama_free};
  std::unique_ptr<llama_sampler, decltype(&llama_sampler_free)> sampler{
      nullptr, llama_sampler_free};
  const llama_vocab* vocabulary{nullptr};
  ChatTemplatePtr chatTemplate;
  ChatTemplate::messages conversation;
  /// @brief The tokens the context keeps evaluated.
  tokens evaluated;
};

using LlamaCPPControllerPtr = LlamaCPPController::LlamaCPPControllerPtr;

}  // namespace llamacppi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LLAMACPPCONTROLLER_CLASS_H
