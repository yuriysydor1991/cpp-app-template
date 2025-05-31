#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/app/Application.h"
#include "src/mongodbcxx/MongoDBController.h"

using namespace app;
using namespace testing;
using namespace mongodbcxxi;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  ~UTEST_Application() { MongoDBController::onMockCreate = nullptr; }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, normal_exit)
{
  MockFunction<void(MongoDBController&)> controllerEnsurer;

  EXPECT_CALL(controllerEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([](MongoDBController& instance) {
        EXPECT_CALL(instance, connect(_)).Times(1).WillOnce(Return(true));
        EXPECT_CALL(instance, get_current_date())
            .Times(1)
            .WillOnce(Return(std::string{"2025-05-31"}));
      }));

  MongoDBController::onMockCreate = controllerEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_Application, connect_failure)
{
  MockFunction<void(MongoDBController&)> controllerEnsurer;

  EXPECT_CALL(controllerEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([](MongoDBController& instance) {
        EXPECT_CALL(instance, connect(_)).Times(1).WillOnce(Return(false));
        EXPECT_CALL(instance, get_current_date()).Times(0);
      }));

  MongoDBController::onMockCreate = controllerEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_NE(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_Application, date_fetch_failure)
{
  MockFunction<void(MongoDBController&)> controllerEnsurer;

  EXPECT_CALL(controllerEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([](MongoDBController& instance) {
        EXPECT_CALL(instance, connect(_)).Times(1).WillOnce(Return(true));
        EXPECT_CALL(instance, get_current_date())
            .Times(1)
            .WillOnce(Return(std::string{}));
      }));

  MongoDBController::onMockCreate = controllerEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_NE(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}
