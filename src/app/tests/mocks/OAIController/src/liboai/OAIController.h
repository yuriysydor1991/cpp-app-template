#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OAICONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OAICONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <memory>
#include <string>

namespace liboaii
{

class OAIController
{
 public:
  using OAIControllerPtr = std::shared_ptr<OAIController>;

  inline static const std::string DEFAULT_MODEL{"gpt-4o-mini"};
  inline static const std::string TOKEN_ENV_VAR{"OPENAI_API_KEY"};

  virtual ~OAIController() = default;
  OAIController() = default;

  MOCK_METHOD(bool, set_token, (const std::string& token));

  MOCK_METHOD(bool, set_token_from_env, ());

  MOCK_METHOD(std::string, ask,
              (const std::string& question, const std::string& model));

  /// @brief The instance handed out by the create method, so a test may set
  /// it's expectations before the tested code asks for a controller.
  inline static OAIControllerPtr instance{};

  inline static OAIControllerPtr create()
  {
    if (instance == nullptr) {
      instance = std::make_shared<OAIController>();
    }

    return instance;
  }
};

using OAIControllerPtr = OAIController::OAIControllerPtr;

}  // namespace liboaii

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OAICONTROLLER_CLASS_H
