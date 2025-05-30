#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/app/Application.h"
#include "src/wt4/Wt4Server.h"

using namespace app;
using namespace testing;
using namespace wt4server;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_Application, no_context_error)
{
  MockFunction<int(std::shared_ptr<app::ApplicationContext>)> staticEnsurer;

  EXPECT_CALL(staticEnsurer, Call(appCtx)).Times(0);

  Wt4Server::run_mock = staticEnsurer.AsStdFunction();

  EXPECT_NE(app->run({}), 0);
}

TEST_F(UTEST_Application, normal_exit)
{
  MockFunction<int(std::shared_ptr<app::ApplicationContext>)> staticEnsurer;

  EXPECT_CALL(staticEnsurer, Call(appCtx)).Times(1).WillOnce(Return(0));

  Wt4Server::run_mock = staticEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_Application, error_exit)
{
  MockFunction<int(std::shared_ptr<app::ApplicationContext>)> staticEnsurer;

  EXPECT_CALL(staticEnsurer, Call(appCtx)).Times(1).WillOnce(Return(1));

  Wt4Server::run_mock = staticEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 1);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}
