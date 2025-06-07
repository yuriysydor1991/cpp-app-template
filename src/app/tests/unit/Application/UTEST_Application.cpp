#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/app/Application.h"
#include "src/qt6/Qt6Initer.h"

using namespace app;
using namespace Qt6i;
using namespace testing;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  ~UTEST_Application() { Qt6Initer::onMockCreate = nullptr; }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, normal_exit)
{
  MockFunction<void(Qt6Initer & instance)> qt6Ensurer;

  EXPECT_CALL(qt6Ensurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](Qt6Initer& instance) {
        EXPECT_CALL(instance, run(appCtx)).Times(1).WillOnce(Return(0));
      }));

  Qt6Initer::onMockCreate = qt6Ensurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_Application, invalid_qt6_status_fail)
{
  MockFunction<void(Qt6Initer & instance)> qt6Ensurer;

  EXPECT_CALL(qt6Ensurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](Qt6Initer& instance) {
        EXPECT_CALL(instance, run(appCtx)).Times(1).WillOnce(Return(1));
      }));

  Qt6Initer::onMockCreate = qt6Ensurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_NE(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}
