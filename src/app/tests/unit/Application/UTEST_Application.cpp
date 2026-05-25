#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/app/Application.h"
#include "src/log/log.h"
#include "src/plotgencpp/PlotGenCppController.h"

using namespace app;
using namespace testing;
using namespace plotgencppi;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
    PlotGenCppController::mock_create =
        std::make_shared<PlotGenCppController::createMockType>();
  }
  virtual ~UTEST_Application() { PlotGenCppController::mock_create.reset(); }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, normal_exit)
{
  PlotGenCppControllerPtr plotterInstance =
      std::make_shared<PlotGenCppController>();

  EXPECT_CALL(*plotterInstance, run(appCtx)).Times(1).WillOnce(Return(true));

  EXPECT_NE(PlotGenCppController::mock_create, nullptr);
  EXPECT_CALL(*PlotGenCppController::mock_create, Call)
      .Times(1)
      .WillOnce(Invoke([&plotterInstance]() { return plotterInstance; }));

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_Application, plotter_fails)
{
  PlotGenCppControllerPtr plotterInstance =
      std::make_shared<PlotGenCppController>();

  EXPECT_CALL(*plotterInstance, run(appCtx)).Times(1).WillOnce(Return(false));

  EXPECT_NE(PlotGenCppController::mock_create, nullptr);
  EXPECT_CALL(*PlotGenCppController::mock_create, Call)
      .Times(1)
      .WillOnce(Invoke([&plotterInstance]() { return plotterInstance; }));

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_NE(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_Application, no_plotter_instance)
{
  EXPECT_NE(PlotGenCppController::mock_create, nullptr);
  EXPECT_CALL(*PlotGenCppController::mock_create, Call)
      .Times(1)
      .WillOnce(Invoke([]() { return PlotGenCppControllerPtr{}; }));

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_NE(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}
