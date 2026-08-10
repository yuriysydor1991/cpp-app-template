#include "src/liboai/OAIController.h"

#include <exception>
#include <memory>
#include <string>

#include "src/log/log.h"

namespace liboaii
{

bool OAIController::set_token(const std::string& token)
{
  if (token.empty()) {
    LOGE("No OpenAI API token provided");
    return false;
  }

  if (!oai.auth.SetKey(token)) {
    LOGE("Fail to set the provided OpenAI API token");
    return false;
  }

  LOGT("The provided OpenAI API token is set");

  return true;
}

bool OAIController::set_token_from_env()
{
  if (!oai.auth.SetKeyEnv(TOKEN_ENV_VAR)) {
    LOGE("Fail to take the OpenAI API token from the "
         << TOKEN_ENV_VAR << " environment variable");
    return false;
  }

  LOGT("The OpenAI API token is taken from the " << TOKEN_ENV_VAR
                                                 << " environment variable");

  return true;
}

std::string OAIController::ask(const std::string& question,
                               const std::string& model)
{
  if (question.empty()) {
    LOGE("No question to ask provided");
    return {};
  }

  const std::string& askedModel = model.empty() ? DEFAULT_MODEL : model;

  liboai::Conversation conversation;

  try {
    if (!conversation.AddUserData(question)) {
      LOGE("Fail to place the question into the conversation");
      return {};
    }

    LOGT("Asking the " << askedModel << " model");

    const liboai::Response response =
        oai.ChatCompletion->create(askedModel, conversation);

    if (!conversation.Update(response)) {
      LOGE("Fail to update the conversation with the received answer");
      return {};
    }
  }
  catch (const std::exception& e) {
    LOGE("The OpenAI API call has failed: " << e.what());
    return {};
  }

  return conversation.GetLastResponse();
}

OAIControllerPtr OAIController::create()
{
  return std::make_shared<OAIController>();
}

}  // namespace liboaii
