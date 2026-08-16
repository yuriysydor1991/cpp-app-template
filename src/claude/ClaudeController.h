#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CLAUDECONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CLAUDECONTROLLER_CLASS_H

#include <memory>
#include <string>
#include <vector>

#include "src/CURL/CURLController.h"

/**
 * @brief The Anthropic Claude API adaptor subsystem namespace.
 */
namespace claudei
{

/**
 * @brief The Claude questioner class.
 *
 * Talks to the Anthropic messages endpoint over the plain HTTP with the
 * libcurl adaptor of the curli subsystem, because Anthropic ships no official
 * C++ SDK.
 */
class ClaudeController
{
 public:
  using ClaudeControllerPtr = std::shared_ptr<ClaudeController>;

  /// @brief The model asked when no other one is requested.
  inline static const std::string DEFAULT_MODEL{"claude-opus-5"};

  /// @brief The environment variable holding the Anthropic API token when no
  /// token is given in the command line.
  inline static const std::string TOKEN_ENV_VAR{"ANTHROPIC_API_KEY"};

  /// @brief The Anthropic messages endpoint to send the questions to.
  inline static const std::string API_URL{
      "https://api.anthropic.com/v1/messages"};

  /// @brief The Anthropic API version the requests are built for. Required
  /// by the endpoint in the anthropic-version header.
  inline static const std::string API_VERSION{"2023-06-01"};

  /// @brief The answer length limit in tokens. Required by the endpoint, so
  /// it has no server side default to fall back to.
  inline static constexpr const unsigned int DEFAULT_MAX_TOKENS{16000U};

  virtual ~ClaudeController() = default;
  ClaudeController();
  explicit ClaudeController(curli::CURLControllerPtr curlController);
  ClaudeController(const ClaudeController&) = delete;
  ClaudeController(ClaudeController&&) = delete;

  /**
   * @brief Sets the given token as the Anthropic API authorization key.
   *
   * @param apiToken The Anthropic API token to authorize the further calls
   * with.
   *
   * @return Returns true on success and false in case of any error.
   */
  virtual bool set_token(const std::string& apiToken);

  /**
   * @brief Takes the Anthropic API authorization key from the TOKEN_ENV_VAR
   * environment variable.
   *
   * @return Returns true on success and false in case of any error.
   */
  virtual bool set_token_from_env();

  /**
   * @brief Asks the Claude model the given question and waits for it's answer.
   *
   * Requires an authorization token set by the set_token or the
   * set_token_from_env method beforehand.
   *
   * @param question The question to ask the model about.
   * @param model The model to ask. The DEFAULT_MODEL one is asked when the
   * value is empty.
   *
   * @return Returns the model answer or an empty string in case of any error.
   */
  virtual std::string ask(const std::string& question,
                          const std::string& model);

  static ClaudeControllerPtr create();

  static ClaudeControllerPtr create(curli::CURLControllerPtr curlController);

 private:
  /**
   * @brief Builds the messages endpoint request body.
   *
   * @param question The question to place into the only user message.
   * @param model The model identifier to ask.
   *
   * @return Returns the serialized JSON request body.
   */
  std::string build_request(const std::string& question,
                            const std::string& model) const;

  /**
   * @brief Builds the HTTP headers the messages endpoint requires.
   *
   * @return Returns the headers, each one in the "Name: value" form.
   */
  std::vector<std::string> build_headers() const;

  /**
   * @brief Takes the answer text out of the messages endpoint response body.
   *
   * The response carries an array of the typed content blocks rather than
   * a single string, so the text of every text block is concatenated.
   *
   * @param response The received JSON response body.
   *
   * @return Returns the answer text or an empty string in case of any error.
   */
  std::string extract_answer(const std::string& response) const;

  curli::CURLControllerPtr curl;
  std::string token;
};

using ClaudeControllerPtr = ClaudeController::ClaudeControllerPtr;

}  // namespace claudei

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CLAUDECONTROLLER_CLASS_H
