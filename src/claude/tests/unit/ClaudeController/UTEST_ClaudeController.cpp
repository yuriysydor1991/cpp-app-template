#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "NoWaitClaudeController.h"
#include "src/CURL/CURLController.h"
#include "src/claude/ClaudeController.h"

using namespace claudei;
using namespace testing;

class UTEST_ClaudeController : public Test
{
 public:
  UTEST_ClaudeController()
      : curl{std::make_shared<curli::CURLController>()},
        controller{std::make_shared<NoWaitClaudeController>(curl)}
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

  /// @brief A minimal well formed messages endpoint answer.
  static std::string answer_with(const std::string& text)
  {
    return R"({"stop_reason":"end_turn","content":[{"type":"text","text":")" +
           text + R"("}]})";
  }

  void expect_answered_with(const std::string& response)
  {
    EXPECT_CALL(*curl, post(_, _, _))
        .WillOnce(DoAll(SaveArg<1>(&sentBody), SaveArg<2>(&sentHeaders),
                        Return(as_buffer(response))));

    EXPECT_CALL(*curl, last_response_successful()).WillRepeatedly(Return(true));
  }

  static constexpr const char* const question = "What is the point of taxes?";
  static constexpr const char* const token = "an-anthropic-api-token";

  std::string sentBody;
  std::vector<std::string> sentHeaders;

  std::shared_ptr<curli::CURLController> curl;
  std::shared_ptr<ClaudeController> controller;
};

TEST_F(UTEST_ClaudeController, empty_token_rejected)
{
  EXPECT_FALSE(controller->set_token({}));
}

TEST_F(UTEST_ClaudeController, no_token_no_call)
{
  EXPECT_CALL(*curl, post(_, _, _)).Times(0);

  EXPECT_TRUE(controller->ask(question, {}).empty());
}

TEST_F(UTEST_ClaudeController, no_question_no_call)
{
  EXPECT_TRUE(controller->set_token(token));

  EXPECT_CALL(*curl, post(_, _, _)).Times(0);

  EXPECT_TRUE(controller->ask({}, {}).empty());
}

TEST_F(UTEST_ClaudeController, request_carries_the_question_and_the_model)
{
  static const std::string model{"claude-sonnet-5-5"};

  EXPECT_TRUE(controller->set_token(token));

  expect_answered_with(answer_with("To fund the public services."));

  EXPECT_EQ(controller->ask(question, model), "To fund the public services.");

  const auto sent = nlohmann::json::parse(sentBody, nullptr, false);

  ASSERT_FALSE(sent.is_discarded());

  EXPECT_EQ(sent["model"], model);
  EXPECT_EQ(sent["max_tokens"], ClaudeController::DEFAULT_MAX_TOKENS);
  ASSERT_TRUE(sent["messages"].is_array());
  ASSERT_EQ(sent["messages"].size(), 1U);
  EXPECT_EQ(sent["messages"][0]["role"], "user");
  EXPECT_EQ(sent["messages"][0]["content"], question);
}

TEST_F(UTEST_ClaudeController, default_model_asked_when_none_given)
{
  EXPECT_TRUE(controller->set_token(token));

  expect_answered_with(answer_with("An answer."));

  EXPECT_EQ(controller->ask(question, {}), "An answer.");

  const auto sent = nlohmann::json::parse(sentBody, nullptr, false);

  ASSERT_FALSE(sent.is_discarded());

  EXPECT_EQ(sent["model"], ClaudeController::DEFAULT_MODEL);
}

TEST_F(UTEST_ClaudeController, headers_carry_the_token_and_the_api_version)
{
  EXPECT_TRUE(controller->set_token(token));

  expect_answered_with(answer_with("An answer."));

  EXPECT_FALSE(controller->ask(question, {}).empty());

  EXPECT_TRUE(has_header(sentHeaders, std::string{"x-api-key: "} + token));
  EXPECT_TRUE(has_header(
      sentHeaders, "anthropic-version: " + ClaudeController::API_VERSION));
  EXPECT_TRUE(has_header(sentHeaders, "content-type: application/json"));
}

TEST_F(UTEST_ClaudeController, only_the_text_blocks_reach_the_answer)
{
  EXPECT_TRUE(controller->set_token(token));

  expect_answered_with(R"({"stop_reason":"end_turn","content":[)"
                       R"({"type":"thinking","thinking":""},)"
                       R"({"type":"text","text":"To fund "},)"
                       R"({"type":"text","text":"the public services."}]})");

  EXPECT_EQ(controller->ask(question, {}), "To fund the public services.");
}

TEST_F(UTEST_ClaudeController, refusal_gives_no_answer)
{
  EXPECT_TRUE(controller->set_token(token));

  expect_answered_with(
      R"({"stop_reason":"refusal","stop_details":{"type":"refusal",)"
      R"("category":"cyber"},"content":[]})");

  EXPECT_TRUE(controller->ask(question, {}).empty());
}

TEST_F(UTEST_ClaudeController, reported_api_error_gives_no_answer)
{
  EXPECT_TRUE(controller->set_token(token));

  EXPECT_CALL(*curl, post(_, _, _))
      .WillOnce(Return(
          as_buffer(R"({"type":"error","error":{"type":"authentication_error",)"
                    R"("message":"invalid x-api-key"}})")));

  EXPECT_CALL(*curl, last_response_successful()).WillRepeatedly(Return(false));
  EXPECT_CALL(*curl, last_response_code()).WillRepeatedly(Return(401L));

  EXPECT_TRUE(controller->ask(question, {}).empty());
}

TEST_F(UTEST_ClaudeController, unparsable_response_gives_no_answer)
{
  EXPECT_TRUE(controller->set_token(token));

  expect_answered_with("<html>a gateway error page</html>");

  EXPECT_TRUE(controller->ask(question, {}).empty());
}

TEST_F(UTEST_ClaudeController, empty_response_gives_no_answer)
{
  EXPECT_TRUE(controller->set_token(token));

  EXPECT_CALL(*curl, post(_, _, _))
      .Times(ClaudeController::MAX_ATTEMPTS)
      .WillRepeatedly(Return(curli::CURLController::download_buffer{}));

  EXPECT_TRUE(controller->ask(question, {}).empty());
}

TEST_F(UTEST_ClaudeController, contentless_response_gives_no_answer)
{
  EXPECT_TRUE(controller->set_token(token));

  expect_answered_with(R"({"stop_reason":"end_turn"})");

  EXPECT_TRUE(controller->ask(question, {}).empty());
}

TEST_F(UTEST_ClaudeController, an_overloaded_endpoint_is_asked_again)
{
  EXPECT_TRUE(controller->set_token(token));

  EXPECT_CALL(*curl, post(_, _, _))
      .WillOnce(Return(
          as_buffer(R"({"type":"error","error":{"type":"overloaded_error",)"
                    R"("message":"Overloaded"}})")))
      .WillOnce(Return(as_buffer(answer_with("Public goods."))));

  EXPECT_CALL(*curl, last_response_code())
      .WillOnce(Return(529L))
      .WillRepeatedly(Return(200L));
  EXPECT_CALL(*curl, last_response_successful()).WillRepeatedly(Return(true));

  EXPECT_EQ(controller->ask(question, {}), "Public goods.");
}

TEST_F(UTEST_ClaudeController, a_failing_endpoint_is_given_up_on)
{
  EXPECT_TRUE(controller->set_token(token));

  EXPECT_CALL(*curl, post(_, _, _))
      .Times(ClaudeController::MAX_ATTEMPTS)
      .WillRepeatedly(
          Return(as_buffer(R"({"type":"error","error":{"type":"api_error",)"
                           R"("message":"Internal server error"}})")));

  EXPECT_CALL(*curl, last_response_code()).WillRepeatedly(Return(500L));
  EXPECT_CALL(*curl, last_response_successful()).WillRepeatedly(Return(false));

  EXPECT_TRUE(controller->ask(question, {}).empty());
}

TEST_F(UTEST_ClaudeController, a_rejected_request_is_not_asked_again)
{
  EXPECT_TRUE(controller->set_token(token));

  EXPECT_CALL(*curl, post(_, _, _))
      .WillOnce(Return(as_buffer(
          R"({"type":"error","error":{"type":"invalid_request_error",)"
          R"("message":"max_tokens: too large"}})")));

  EXPECT_CALL(*curl, last_response_code()).WillRepeatedly(Return(400L));
  EXPECT_CALL(*curl, last_response_successful()).WillRepeatedly(Return(false));

  EXPECT_TRUE(controller->ask(question, {}).empty());
}
