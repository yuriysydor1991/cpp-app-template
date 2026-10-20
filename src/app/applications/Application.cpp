#include "src/app/applications/Application.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <string>

#include "project-global-decls.h"
#include "src/LlamaCPP/LlamaCPPController.h"
#include "src/app/CMDParamNames.h"
#include "src/app/DataLocator.h"
#include "src/log/log.h"

namespace app
{

namespace
{

/// @brief Prints the answer of the model piece by piece as it comes, while the
/// Ctrl+C keys stop it.
bool answer(llamacppi::LlamaCPPController& llama, const std::string& question,
            const ApplicationContext& ctx)
{
  const auto print = [&ctx](const std::string& piece) {
    std::cout << piece << std::flush;
    return !ctx.get_stop();
  };

  const bool answered = llama.ask(question, print).has_value();

  std::cout << std::endl;

  if (!answered) {
    LOGE("Fail to answer the question");
  }

  return answered;
}

}  // namespace

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  const std::string model =
      ctx->get_model_path().empty()
          ? DataLocator::locate(project_decls::PROJECT_LLAMACPP_MODEL_PATH)
          : ctx->get_model_path();

  auto llama = llamacppi::LlamaCPPController::create();

  assert(llama != nullptr);

  if (!llama->init(model)) {
    LOGE("Fail to load the language model, point at a GGUF one with the "
         << CMDParamNames::MODELW << " or " << CMDParamNames::MODEL
         << " <path> command line parameter");
    return INVALID;
  }

  // Insert your own questions here.
  if (!ctx->get_question().empty()) {
    return answer(*llama, ctx->get_question(), *ctx) ? 0 : INVALID;
  }

  LOGI("Type the questions line by line, Ctrl+D ends the chat");

  for (std::string question;
       !ctx->get_stop() && std::getline(std::cin, question);) {
    if (!question.empty() && !answer(*llama, question, *ctx)) {
      return INVALID;
    }
  }

  return 0;
}

}  // namespace app
