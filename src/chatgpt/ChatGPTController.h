#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CHATGPTCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CHATGPTCONTROLLER_CLASS_H

#include <memory>
#include <string>
#include <vector>

#include "src/CURL/CURLController.h"

/**
 * @brief The OpenAI ChatGPT API adaptor subsystem namespace.
 */
namespace chatgpti
{

/**
 * @brief The ChatGPT questioner class.
 *
 * Talks to the OpenAI responses endpoint over the plain HTTP with the libcurl
 * adaptor of the curli subsystem, because OpenAI ships no official C++ SDK.
 */
class ChatGPTController
{
 public:
  using ChatGPTControllerPtr = std::shared_ptr<ChatGPTController>;

  /// @brief The model asked when no other one is requested. This is the alias
  /// of the flagship model of the family, so it follows it's releases.
  inline static const std::string DEFAULT_MODEL{"gpt-5.6"};

  /// @brief The environment variable holding the OpenAI API token when no
  /// token is given in the command line.
  inline static const std::string TOKEN_ENV_VAR{"OPENAI_API_KEY"};

  /// @brief The OpenAI responses endpoint to send the questions to.
  inline static const std::string API_URL{
      "https://api.openai.com/v1/responses"};

  virtual ~ChatGPTController() = default;
  ChatGPTController();
  explicit ChatGPTController(curli::CURLControllerPtr curlController);
  ChatGPTController(const ChatGPTController&) = delete;
  ChatGPTController(ChatGPTController&&) = delete;

  /**
   * @brief Sets the given token as the OpenAI API authorization key.
   *
   * @param apiToken The OpenAI API token to authorize the further calls with.
   *
   * @return Returns true on success and false in case of any error.
   */
  virtual bool set_token(const std::string& apiToken);

  /**
   * @brief Takes the OpenAI API authorization key from the TOKEN_ENV_VAR
   * environment variable.
   *
   * @return Returns true on success and false in case of any error.
   */
  virtual bool set_token_from_env();

  /**
   * @brief Asks the ChatGPT model the given question and waits for it's
   * answer.
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

  static ChatGPTControllerPtr create();

  static ChatGPTControllerPtr create(curli::CURLControllerPtr curlController);

 private:
  /// @brief The HTTP status code of a successfully answered request.
  inline static constexpr const long HTTP_OK{200L};

  /**
   * @brief Builds the responses endpoint request body.
   *
   * @param question The question to place into the request input.
   * @param model The model identifier to ask.
   *
   * @return Returns the serialized JSON request body.
   */
  std::string build_request(const std::string& question,
                            const std::string& model) const;

  /**
   * @brief Builds the HTTP headers the responses endpoint requires.
   *
   * @return Returns the headers, each one in the "Name: value" form.
   */
  std::vector<std::string> build_headers() const;

  /**
   * @brief Takes the answer text out of the responses endpoint response body.
   *
   * The response carries an array of the typed output items rather than a
   * single string, and the endpoint documentation warns that the answer is
   * not necessarily the first of them, so every message item is walked and
   * the text of it's every text block is concatenated.
   *
   * @param response The received JSON response body.
   *
   * @return Returns the answer text or an empty string in case of any error.
   */
  std::string extract_answer(const std::string& response) const;

  curli::CURLControllerPtr curl;
  std::string token;
};

using ChatGPTControllerPtr = ChatGPTController::ChatGPTControllerPtr;

}  // namespace chatgpti

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CHATGPTCONTROLLER_CLASS_H
