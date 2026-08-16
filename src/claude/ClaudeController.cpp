#include "src/claude/ClaudeController.h"

#include <cstdlib>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "src/CURL/CURLController.h"
#include "src/log/log.h"

namespace claudei
{

namespace
{

/**
 * @brief Reads a string field of the given JSON object.
 *
 * Preferred over the nlohmann value method, which the GCC optimizer inlines
 * into a chain that raises a false positive null dereference warning.
 *
 * @param object The JSON object to read the field of.
 * @param name The name of the field to read.
 *
 * @return Returns the field value or an empty string when the object holds
 * no string under that name.
 */
std::string string_field(const nlohmann::json& object, const char* const name)
{
  if (!object.is_object() || !object.contains(name)) {
    return {};
  }

  const auto& field = object.at(name);

  if (!field.is_string()) {
    return {};
  }

  return field.get<std::string>();
}

}  // namespace

ClaudeController::ClaudeController() : curl{curli::CURLController::create()} {}

ClaudeController::ClaudeController(curli::CURLControllerPtr curlController)
    : curl{curlController}
{
}

bool ClaudeController::set_token(const std::string& apiToken)
{
  if (apiToken.empty()) {
    LOGE("No Anthropic API token provided");
    return false;
  }

  token = apiToken;

  LOGT("The provided Anthropic API token is set");

  return true;
}

bool ClaudeController::set_token_from_env()
{
  const char* const envToken = std::getenv(TOKEN_ENV_VAR.c_str());

  if (envToken == nullptr || *envToken == '\0') {
    LOGE("Fail to take the Anthropic API token from the "
         << TOKEN_ENV_VAR << " environment variable");
    return false;
  }

  token = envToken;

  LOGT("The Anthropic API token is taken from the " << TOKEN_ENV_VAR
                                                    << " environment variable");

  return true;
}

std::string ClaudeController::build_request(const std::string& question,
                                            const std::string& model) const
{
  nlohmann::json message;

  message["role"] = "user";
  message["content"] = question;

  nlohmann::json request;

  request["model"] = model;
  request["max_tokens"] = DEFAULT_MAX_TOKENS;
  request["messages"] = nlohmann::json::array();
  request["messages"].push_back(message);

  return request.dump();
}

std::vector<std::string> ClaudeController::build_headers() const
{
  return {"content-type: application/json", "anthropic-version: " + API_VERSION,
          "x-api-key: " + token};
}

std::string ClaudeController::extract_answer(const std::string& response) const
{
  const auto parsed = nlohmann::json::parse(response, nullptr, false);

  if (parsed.is_discarded() || !parsed.is_object()) {
    LOGE("Fail to parse the Anthropic API response");
    return {};
  }

  if (parsed.contains("error") && parsed["error"].is_object()) {
    const auto& error = parsed["error"];

    LOGE("The Anthropic API reports an error: "
         << string_field(error, "type") << ": "
         << string_field(error, "message"));

    return {};
  }

  const std::string stopReason = string_field(parsed, "stop_reason");

  if (stopReason == "refusal") {
    LOGE("The model declined to answer the given question");
    return {};
  }

  if (!parsed.contains("content") || !parsed["content"].is_array()) {
    LOGE("No content blocks within the Anthropic API response");
    return {};
  }

  std::string answer;

  // The content is an array of the typed blocks rather than a single string,
  // so anything but the text ones (a thinking block, for instance) is skipped.
  for (const auto& block : parsed["content"]) {
    if (string_field(block, "type") == "text") {
      answer += string_field(block, "text");
    }
  }

  if (stopReason == "max_tokens") {
    LOGW("The answer is cut by the " << DEFAULT_MAX_TOKENS
                                     << " answer tokens limit");
  }

  return answer;
}

std::string ClaudeController::ask(const std::string& question,
                                  const std::string& model)
{
  if (question.empty()) {
    LOGE("No question to ask provided");
    return {};
  }

  if (token.empty()) {
    LOGE("No Anthropic API token set to authorize the call with");
    return {};
  }

  if (curl == nullptr) {
    LOGE("No valid HTTP transport available");
    return {};
  }

  const std::string& askedModel = model.empty() ? DEFAULT_MODEL : model;

  LOGT("Asking the " << askedModel << " model");

  const auto& received =
      curl->post(API_URL, build_request(question, askedModel), build_headers());

  const std::string response{received.cbegin(), received.cend()};

  if (response.empty()) {
    LOGE("No response received from the Anthropic API");
    return {};
  }

  if (!curl->last_response_successfull()) {
    LOGE("The Anthropic API answered with the " << curl->last_response_code()
                                                << " HTTP status code");
  }

  return extract_answer(response);
}

ClaudeControllerPtr ClaudeController::create()
{
  return std::make_shared<ClaudeController>();
}

ClaudeControllerPtr ClaudeController::create(
    curli::CURLControllerPtr curlController)
{
  return std::make_shared<ClaudeController>(curlController);
}

}  // namespace claudei
