#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdlib>
#include <memory>

#include "src/liboai/OAIController.h"

using namespace liboaii;
using namespace testing;

/**
 * @brief Covers the OAIController paths that never reach the OpenAI servers,
 * so the tests run offline and with no real token.
 */
class UTEST_OAIController : public Test
{
 public:
  UTEST_OAIController() { unsetenv(OAIController::TOKEN_ENV_VAR.c_str()); }

  ~UTEST_OAIController() override
  {
    unsetenv(OAIController::TOKEN_ENV_VAR.c_str());
  }

  static constexpr const char* const token = "an-openai-api-token";

  OAIControllerPtr controller{OAIController::create()};
};

TEST_F(UTEST_OAIController, create_returns_valid_instance)
{
  EXPECT_NE(controller, nullptr);
}

TEST_F(UTEST_OAIController, empty_token_rejected)
{
  EXPECT_FALSE(controller->set_token({}));
}

TEST_F(UTEST_OAIController, token_accepted)
{
  EXPECT_TRUE(controller->set_token(token));
}

TEST_F(UTEST_OAIController, absent_env_token_rejected)
{
  EXPECT_FALSE(controller->set_token_from_env());
}

TEST_F(UTEST_OAIController, env_token_accepted)
{
  ASSERT_EQ(setenv(OAIController::TOKEN_ENV_VAR.c_str(), token, 1), 0);

  EXPECT_TRUE(controller->set_token_from_env());
}

TEST_F(UTEST_OAIController, no_question_no_answer)
{
  EXPECT_TRUE(controller->set_token(token));

  EXPECT_TRUE(controller->ask({}, OAIController::DEFAULT_MODEL).empty());
}
