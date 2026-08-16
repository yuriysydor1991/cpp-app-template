#include "src/chatgpt/ChatGPTController.h"

#include <cstdlib>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "src/CURL/CURLController.h"
#include "src/log/log.h"

namespace chatgpti
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

ChatGPTController::ChatGPTController() : curl{curli::CURLController::create()}
{
}

ChatGPTController::ChatGPTController(curli::CURLControllerPtr curlController)
    : curl{curlController}
{
}

bool ChatGPTController::set_token(const std::string& apiToken)
{
  if (apiToken.empty()) {
    LOGE("No OpenAI API token provided");
    return false;
  }

  token = apiToken;

  LOGT("The provided OpenAI API token is set");

  return true;
}

bool ChatGPTController::set_token_from_env()
{
  const char* const envToken = std::getenv(TOKEN_ENV_VAR.c_str());

  if (envToken == nullptr || *envToken == '\0') {
    LOGE("Fail to take the OpenAI API token from the "
         << TOKEN_ENV_VAR << " environment variable");
    return false;
  }

  token = envToken;

  LOGT("The OpenAI API token is taken from the " << TOKEN_ENV_VAR
                                                 << " environment variable");

  return true;
}

std::string ChatGPTController::build_request(const std::string& question,
                                             const std::string& model) const
{
  nlohmann::json request;

  request["model"] = model;
  request["input"] = question;

  return request.dump();
}

std::vector<std::string> ChatGPTController::build_headers() const
{
  return {"content-type: application/json", "authorization: Bearer " + token};
}

std::string ChatGPTController::extract_answer(const std::string& response) const
{
  const auto parsed = nlohmann::json::parse(response, nullptr, false);

  if (parsed.is_discarded() || !parsed.is_object()) {
    LOGE("Fail to parse the OpenAI API response");
    return {};
  }

  // The field holds a null on a success, so only an object of it's own
  // reports a failure.
  if (parsed.contains("error") && parsed["error"].is_object()) {
    const auto& error = parsed["error"];

    LOGE("The OpenAI API reports an error: " << string_field(error, "code")
                                             << ": "
                                             << string_field(error, "message"));

    return {};
  }

  if (!parsed.contains("output") || !parsed["output"].is_array()) {
    LOGE("No output items within the OpenAI API response");
    return {};
  }

  std::string answer;

  // The output is an array of the typed items rather than a single string,
  // and a reasoning item may well precede the answering message one, so
  // every message is walked instead of the first item only.
  for (const auto& item : parsed["output"]) {
    if (string_field(item, "type") != "message" || !item.contains("content") ||
        !item["content"].is_array()) {
      continue;
    }

    for (const auto& block : item["content"]) {
      const std::string blockType = string_field(block, "type");

      if (blockType == "output_text") {
        answer += string_field(block, "text");
      } else if (blockType == "refusal") {
        LOGE("The model declined to answer the given question: "
             << string_field(block, "refusal"));
      }
    }
  }

  if (string_field(parsed, "status") == "incomplete") {
    const std::string reason =
        parsed.contains("incomplete_details")
            ? string_field(parsed["incomplete_details"], "reason")
            : std::string{};

    LOGW("The answer is incomplete, the reported reason is " << reason);
  }

  return answer;
}

std::string ChatGPTController::ask(const std::string& question,
                                   const std::string& model)
{
  if (question.empty()) {
    LOGE("No question to ask provided");
    return {};
  }

  if (token.empty()) {
    LOGE("No OpenAI API token set to authorize the call with");
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
    LOGE("No response received from the OpenAI API");
    return {};
  }

  const long httpCode = curl->last_response_code();

  if (httpCode != HTTP_OK) {
    LOGE("The OpenAI API answered with the " << httpCode
                                             << " HTTP status code");
  }

  return extract_answer(response);
}

ChatGPTControllerPtr ChatGPTController::create()
{
  return std::make_shared<ChatGPTController>();
}

ChatGPTControllerPtr ChatGPTController::create(
    curli::CURLControllerPtr curlController)
{
  return std::make_shared<ChatGPTController>(curlController);
}

}  // namespace chatgpti
