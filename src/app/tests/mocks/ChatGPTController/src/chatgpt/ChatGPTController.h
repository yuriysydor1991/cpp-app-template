#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CHATGPTCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CHATGPTCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <memory>
#include <string>

namespace chatgpti
{

class ChatGPTController
{
 public:
  using ChatGPTControllerPtr = std::shared_ptr<ChatGPTController>;

  inline static const std::string DEFAULT_MODEL{"gpt-5.6"};
  inline static const std::string TOKEN_ENV_VAR{"OPENAI_API_KEY"};
  inline static const std::string API_URL{
      "https://api.openai.com/v1/responses"};

  virtual ~ChatGPTController() = default;
  ChatGPTController() = default;

  MOCK_METHOD(bool, set_token, (const std::string& token));

  MOCK_METHOD(bool, set_token_from_env, ());

  MOCK_METHOD(std::string, ask,
              (const std::string& question, const std::string& model));

  /// @brief The instance handed out by the create method, so a test may set
  /// it's expectations before the tested code asks for a controller.
  inline static ChatGPTControllerPtr instance{};

  inline static ChatGPTControllerPtr create()
  {
    if (instance == nullptr) {
      instance = std::make_shared<ChatGPTController>();
    }

    return instance;
  }
};

using ChatGPTControllerPtr = ChatGPTController::ChatGPTControllerPtr;

}  // namespace chatgpti

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CHATGPTCONTROLLER_CLASS_H
