#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/app/applications/Application.h"
#include "src/gtkmm4/Gtkmm4Controller.h"

using namespace app;
using namespace Gtkmm4i;
using namespace testing;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  ~UTEST_Application() { Gtkmm4Controller::onMockCreate = nullptr; }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, normal_exit)
{
  MockFunction<void(Gtkmm4Controller & instance)> controllerEnsurer;

  EXPECT_CALL(controllerEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](Gtkmm4Controller& instance) {
        EXPECT_CALL(instance, run(appCtx)).Times(1).WillOnce(Return(0));
      }));

  Gtkmm4Controller::onMockCreate = controllerEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->get_errors().empty());

  EXPECT_FALSE(appCtx->get_print_help_and_exit());
  EXPECT_FALSE(appCtx->get_print_version_and_exit());
}

TEST_F(UTEST_Application, invalid_exit_status)
{
  MockFunction<void(Gtkmm4Controller & instance)> controllerEnsurer;

  EXPECT_CALL(controllerEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](Gtkmm4Controller& instance) {
        EXPECT_CALL(instance, run(appCtx)).Times(1).WillOnce(Return(1));
      }));

  Gtkmm4Controller::onMockCreate = controllerEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_NE(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->get_errors().empty());

  EXPECT_FALSE(appCtx->get_print_help_and_exit());
  EXPECT_FALSE(appCtx->get_print_version_and_exit());
}
