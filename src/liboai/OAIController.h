#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OAICONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OAICONTROLLER_CLASS_H

#include <liboai.h>

#include <memory>
#include <string>

/**
 * @brief The liboai OpenAI API adaptor subsystem namespace.
 */
namespace liboaii
{

/**
 * @brief The ChatGPT questioner class.
 */
class OAIController
{
 public:
  using OAIControllerPtr = std::shared_ptr<OAIController>;

  /// @brief The chat completion model asked when no other one is requested.
  inline static const std::string DEFAULT_MODEL{"gpt-4o-mini"};

  /// @brief The environment variable holding the OpenAI API token when no
  /// token is given in the command line.
  inline static const std::string TOKEN_ENV_VAR{"OPENAI_API_KEY"};

  virtual ~OAIController() = default;
  OAIController() = default;
  OAIController(const OAIController&) = delete;
  OAIController(OAIController&&) = delete;

  /**
   * @brief Sets the given token as the OpenAI API authorization key.
   *
   * @param token The OpenAI API token to authorize the further calls with.
   *
   * @return Returns true on success and false in case of any error.
   */
  virtual bool set_token(const std::string& token);

  /**
   * @brief Takes the OpenAI API authorization key from the TOKEN_ENV_VAR
   * environment variable.
   *
   * @return Returns true on success and false in case of any error.
   */
  virtual bool set_token_from_env();

  /**
   * @brief Asks the ChatGPT the given question and waits for it's answer.
   *
   * Requires an authorization token set by the set_token or the
   * set_token_from_env method beforehand.
   *
   * @param question The question to ask the model about.
   * @param model The chat completion model to ask. The DEFAULT_MODEL one is
   * asked when the value is empty.
   *
   * @return Returns the model answer or an empty string in case of any error.
   */
  virtual std::string ask(const std::string& question,
                          const std::string& model);

  static OAIControllerPtr create();

 private:
  liboai::OpenAI oai;
};

using OAIControllerPtr = OAIController::OAIControllerPtr;

}  // namespace liboaii

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OAICONTROLLER_CLASS_H
