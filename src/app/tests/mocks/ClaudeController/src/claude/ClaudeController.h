#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CLAUDECONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CLAUDECONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <memory>
#include <string>

namespace claudei
{

class ClaudeController
{
 public:
  using ClaudeControllerPtr = std::shared_ptr<ClaudeController>;

  inline static const std::string DEFAULT_MODEL{"claude-opus-5"};
  inline static const std::string TOKEN_ENV_VAR{"ANTHROPIC_API_KEY"};
  inline static const std::string API_URL{
      "https://api.anthropic.com/v1/messages"};
  inline static const std::string API_VERSION{"2023-06-01"};
  inline static constexpr const unsigned int DEFAULT_MAX_TOKENS{16000U};

  virtual ~ClaudeController() = default;
  ClaudeController() = default;

  MOCK_METHOD(bool, set_token, (const std::string& token));

  MOCK_METHOD(bool, set_token_from_env, ());

  MOCK_METHOD(std::string, ask,
              (const std::string& question, const std::string& model));

  /// @brief The instance handed out by the create method, so a test may set
  /// it's expectations before the tested code asks for a controller.
  inline static ClaudeControllerPtr instance{};

  inline static ClaudeControllerPtr create()
  {
    if (instance == nullptr) {
      instance = std::make_shared<ClaudeController>();
    }

    return instance;
  }
};

using ClaudeControllerPtr = ClaudeController::ClaudeControllerPtr;

}  // namespace claudei

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CLAUDECONTROLLER_CLASS_H
