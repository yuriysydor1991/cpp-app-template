#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/app/Application.h"
#include "src/sdbuscxx/SDBusCxxController.h"

using namespace app;
using namespace sdbuscxxi;
using namespace testing;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)},
        controller{std::make_shared<NiceMock<SDBusCxxController>>()}
  {
    // Application::run() acquires its controller through the static
    // SDBusCxxController::create() factory. Route that to the fixture's mock so
    // the interaction with the controller can be observed without a real D-Bus
    // connection (and without linking against sdbus-c++).
    SDBusCxxController::onMockCreate = [this]() { return controller; };
  }

  ~UTEST_Application() override { SDBusCxxController::onMockCreate = nullptr; }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
  std::shared_ptr<NiceMock<SDBusCxxController>> controller;
};

TEST_F(UTEST_Application, no_context_error)
{
  EXPECT_CALL(*controller, run(_)).Times(0);

  EXPECT_NE(app->run({}), 0);
}

TEST_F(UTEST_Application, normal_exit)
{
  EXPECT_CALL(*appCtx, push_error(_)).Times(0);
  EXPECT_CALL(*controller, run(appCtx)).WillOnce(Return(true));

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_Application, controller_run_failure_is_reported)
{
  EXPECT_CALL(*controller, run(appCtx)).WillOnce(Return(false));

  EXPECT_NE(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, controller_creation_failure_is_reported)
{
  SDBusCxxController::onMockCreate = []() { return SDBusCxxControllerPtr{}; };

  EXPECT_CALL(*controller, run(_)).Times(0);

  EXPECT_NE(app->run(appCtx), 0);
}
