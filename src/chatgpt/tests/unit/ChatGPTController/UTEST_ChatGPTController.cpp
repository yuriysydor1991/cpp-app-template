#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "src/CURL/CURLController.h"
#include "src/chatgpt/ChatGPTController.h"

using namespace chatgpti;
using namespace testing;

class UTEST_ChatGPTController : public Test
{
 public:
  UTEST_ChatGPTController()
      : curl{std::make_shared<curli::CURLController>()},
        controller{std::make_shared<ChatGPTController>(curl)}
  {
  }

  static curli::CURLController::download_buffer as_buffer(
      const std::string& data)
  {
    return {data.cbegin(), data.cend()};
  }

  static bool has_header(const std::vector<std::string>& headers,
                         const std::string& expected)
  {
    return std::find(headers.cbegin(), headers.cend(), expected) !=
           headers.cend();
  }

  /// @brief A minimal well formed responses endpoint answer. The reasoning
  /// item ahead of the message one is what the endpoint really sends, so the
  /// answer is never the first output item of a reasoning model.
  static std::string answer_with(const std::string& text)
  {
    return R"({"status":"completed","error":null,"output":[)"
           R"({"type":"reasoning","summary":[]},)"
           R"({"type":"message","role":"assistant","content":[)"
           R"({"type":"output_text","text":")" +
           text + R"("}]}]})";
  }

  void expect_answered_with(const std::string& response)
  {
    EXPECT_CALL(*curl, post(_, _, _))
        .WillOnce(DoAll(SaveArg<1>(&sentBody), SaveArg<2>(&sentHeaders),
                        Return(as_buffer(response))));

    EXPECT_CALL(*curl, last_response_code()).WillRepeatedly(Return(200L));
  }

  static constexpr const char* const question = "What is the point of taxes?";
  static constexpr const char* const token = "an-openai-api-token";

  std::string sentBody;
  std::vector<std::string> sentHeaders;

  std::shared_ptr<curli::CURLController> curl;
  std::shared_ptr<ChatGPTController> controller;
};

TEST_F(UTEST_ChatGPTController, empty_token_rejected)
{
  EXPECT_FALSE(controller->set_token({}));
}

TEST_F(UTEST_ChatGPTController, no_token_no_call)
{
  EXPECT_CALL(*curl, post(_, _, _)).Times(0);

  EXPECT_TRUE(controller->ask(question, {}).empty());
}

TEST_F(UTEST_ChatGPTController, no_question_no_call)
{
  EXPECT_TRUE(controller->set_token(token));

  EXPECT_CALL(*curl, post(_, _, _)).Times(0);

  EXPECT_TRUE(controller->ask({}, {}).empty());
}

TEST_F(UTEST_ChatGPTController, request_carries_the_question_and_the_model)
{
  static const std::string model{"gpt-5.6-terra"};

  EXPECT_TRUE(controller->set_token(token));

  expect_answered_with(answer_with("To fund the public services."));

  EXPECT_EQ(controller->ask(question, model), "To fund the public services.");

  const auto sent = nlohmann::json::parse(sentBody, nullptr, false);

  ASSERT_FALSE(sent.is_discarded());

  EXPECT_EQ(sent["model"], model);
  EXPECT_EQ(sent["input"], question);
}

TEST_F(UTEST_ChatGPTController, the_responses_endpoint_is_asked)
{
  EXPECT_TRUE(controller->set_token(token));

  EXPECT_CALL(*curl, post(ChatGPTController::API_URL, _, _))
      .WillOnce(Return(as_buffer(answer_with("An answer."))));

  EXPECT_CALL(*curl, last_response_code()).WillRepeatedly(Return(200L));

  EXPECT_EQ(controller->ask(question, {}), "An answer.");
}

TEST_F(UTEST_ChatGPTController, default_model_asked_when_none_given)
{
  EXPECT_TRUE(controller->set_token(token));

  expect_answered_with(answer_with("An answer."));

  EXPECT_EQ(controller->ask(question, {}), "An answer.");

  const auto sent = nlohmann::json::parse(sentBody, nullptr, false);

  ASSERT_FALSE(sent.is_discarded());

  EXPECT_EQ(sent["model"], ChatGPTController::DEFAULT_MODEL);
}

TEST_F(UTEST_ChatGPTController, headers_carry_the_token_and_the_content_type)
{
  EXPECT_TRUE(controller->set_token(token));

  expect_answered_with(answer_with("An answer."));

  EXPECT_FALSE(controller->ask(question, {}).empty());

  EXPECT_TRUE(
      has_header(sentHeaders, std::string{"authorization: Bearer "} + token));
  EXPECT_TRUE(has_header(sentHeaders, "content-type: application/json"));
}

TEST_F(UTEST_ChatGPTController, only_the_text_blocks_reach_the_answer)
{
  EXPECT_TRUE(controller->set_token(token));

  expect_answered_with(
      R"({"status":"completed","output":[)"
      R"({"type":"reasoning","summary":[]},)"
      R"({"type":"message","role":"assistant","content":[)"
      R"({"type":"output_text","text":"To fund "},)"
      R"({"type":"output_text","text":"the public services."}]}]})");

  EXPECT_EQ(controller->ask(question, {}), "To fund the public services.");
}

TEST_F(UTEST_ChatGPTController, refusal_gives_no_answer)
{
  EXPECT_TRUE(controller->set_token(token));

  expect_answered_with(
      R"({"status":"completed","output":[)"
      R"({"type":"message","role":"assistant","content":[)"
      R"({"type":"refusal","refusal":"I cannot help with that."}]}]})");

  EXPECT_TRUE(controller->ask(question, {}).empty());
}

TEST_F(UTEST_ChatGPTController, an_incomplete_answer_is_still_given)
{
  EXPECT_TRUE(controller->set_token(token));

  expect_answered_with(
      R"({"status":"incomplete",)"
      R"("incomplete_details":{"reason":"max_output_tokens"},"output":[)"
      R"({"type":"message","role":"assistant","content":[)"
      R"({"type":"output_text","text":"To fund the pub"}]}]})");

  EXPECT_EQ(controller->ask(question, {}), "To fund the pub");
}

TEST_F(UTEST_ChatGPTController, reported_api_error_gives_no_answer)
{
  EXPECT_TRUE(controller->set_token(token));

  EXPECT_CALL(*curl, post(_, _, _))
      .WillOnce(
          Return(as_buffer(R"({"error":{"code":"invalid_api_key",)"
                           R"("message":"Incorrect API key provided"}})")));

  EXPECT_CALL(*curl, last_response_code()).WillRepeatedly(Return(401L));

  EXPECT_TRUE(controller->ask(question, {}).empty());
}

TEST_F(UTEST_ChatGPTController, unparsable_response_gives_no_answer)
{
  EXPECT_TRUE(controller->set_token(token));

  expect_answered_with("<html>a gateway error page</html>");

  EXPECT_TRUE(controller->ask(question, {}).empty());
}

TEST_F(UTEST_ChatGPTController, empty_response_gives_no_answer)
{
  EXPECT_TRUE(controller->set_token(token));

  EXPECT_CALL(*curl, post(_, _, _))
      .WillOnce(Return(curli::CURLController::download_buffer{}));

  EXPECT_TRUE(controller->ask(question, {}).empty());
}

TEST_F(UTEST_ChatGPTController, outputless_response_gives_no_answer)
{
  EXPECT_TRUE(controller->set_token(token));

  expect_answered_with(R"({"status":"completed","error":null})");

  EXPECT_TRUE(controller->ask(question, {}).empty());
}
