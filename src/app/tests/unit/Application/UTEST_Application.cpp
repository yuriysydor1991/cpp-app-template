#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/app/Application.h"
#include "src/sqlite3cpp/SQLiteController.h"

using namespace app;
using namespace testing;
using namespace sqlite3i;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  ~UTEST_Application() { SQLiteController::onMockCreate = nullptr; }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, normal_exit)
{
  MockFunction<void(SQLiteController&)> controllerEnsurer;

  EXPECT_CALL(controllerEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([](SQLiteController& instance) {
        EXPECT_CALL(instance, connect).Times(1).WillOnce(Return(true));
        EXPECT_CALL(instance, get_current_date)
            .Times(1)
            .WillOnce(Return(std::string{"2025-05-29"}));
      }));

  SQLiteController::onMockCreate = controllerEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_Application, no_connect_failure)
{
  MockFunction<void(SQLiteController&)> controllerEnsurer;

  EXPECT_CALL(controllerEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([](SQLiteController& instance) {
        EXPECT_CALL(instance, connect).Times(1).WillOnce(Return(false));
        EXPECT_CALL(instance, get_current_date).Times(0);
      }));

  SQLiteController::onMockCreate = controllerEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_NE(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}
