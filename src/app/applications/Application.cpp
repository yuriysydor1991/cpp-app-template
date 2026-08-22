#include "src/app/applications/Application.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <string>

#include "src/app/CMDParamNames.h"
#include "src/chatgpt/ChatGPTController.h"
#include "src/log/log.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  if (ctx->get_chatgpt_question().empty()) {
    LOGI("No question provided");

    std::cout << "Ask the ChatGPT model about something by providing a "
                 "question with the "
              << CMDParamNames::QUESTIONW << " command line parameter."
              << std::endl;

    return 0;
  }

  auto controller = chatgpti::ChatGPTController::create();

  assert(controller != nullptr);

  const bool tokenIsSet = ctx->get_chatgpt_token().empty()
                              ? controller->set_token_from_env()
                              : controller->set_token(ctx->get_chatgpt_token());

  if (!tokenIsSet) {
    ctx->push_error("No valid OpenAI API token provided. Give it with the " +
                    CMDParamNames::TOKENW +
                    " command line parameter or "
                    "through the " +
                    chatgpti::ChatGPTController::TOKEN_ENV_VAR +
                    " environment variable.");
    LOGE("No valid OpenAI API token provided");
    return INVALID;
  }

  const std::string answer =
      controller->ask(ctx->get_chatgpt_question(), ctx->get_chatgpt_model());

  if (answer.empty()) {
    ctx->push_error("No answer received from the ChatGPT model.");
    LOGE("No answer received from the ChatGPT model");
    return INVALID;
  }

  LOGI("The ChatGPT answer is received");

  std::cout << answer << std::endl;

  return 0;
}

}  // namespace app
