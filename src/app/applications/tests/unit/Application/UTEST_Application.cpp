#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/app/applications/Application.h"
#include "src/liboai/OAIController.h"

using namespace app;
using namespace testing;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
    liboaii::OAIController::instance =
        std::make_shared<liboaii::OAIController>();
  }

  ~UTEST_Application() override { liboaii::OAIController::instance.reset(); }

  liboaii::OAIController& oai() { return *liboaii::OAIController::instance; }

  static constexpr const char* const question = "What is the point of taxes?";
  static constexpr const char* const token = "an-openai-api-token";

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, normal_exit)
{
  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->get_errors().empty());

  EXPECT_FALSE(appCtx->get_print_help_and_exit());
  EXPECT_FALSE(appCtx->get_print_version_and_exit());
}

TEST_F(UTEST_Application, token_from_env_when_no_token_given)
{
  appCtx->set_openai_question(question);

  EXPECT_CALL(oai(), set_token(_)).Times(0);
  EXPECT_CALL(oai(), set_token_from_env()).WillOnce(Return(true));
  EXPECT_CALL(oai(), ask(std::string{question}, std::string{}))
      .WillOnce(Return("To fund the public services."));

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, given_token_and_model_are_asked_with)
{
  static const std::string model{"gpt-4o"};

  appCtx->set_openai_question(question);
  appCtx->set_openai_token(token);
  appCtx->set_openai_model(model);

  EXPECT_CALL(oai(), set_token_from_env()).Times(0);
  EXPECT_CALL(oai(), set_token(std::string{token})).WillOnce(Return(true));
  EXPECT_CALL(oai(), ask(std::string{question}, model))
      .WillOnce(Return("To fund the public services."));

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, rejected_token_error)
{
  appCtx->set_openai_question(question);
  appCtx->set_openai_token(token);

  EXPECT_CALL(oai(), set_token(_)).WillOnce(Return(false));
  EXPECT_CALL(oai(), ask(_, _)).Times(0);

  EXPECT_CALL(*appCtx, push_error(_)).Times(1);

  EXPECT_NE(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, empty_answer_error)
{
  appCtx->set_openai_question(question);
  appCtx->set_openai_token(token);

  EXPECT_CALL(oai(), set_token(_)).WillOnce(Return(true));
  EXPECT_CALL(oai(), ask(_, _)).WillOnce(Return(std::string{}));

  EXPECT_CALL(*appCtx, push_error(_)).Times(1);

  EXPECT_NE(app->run(appCtx), 0);
}
