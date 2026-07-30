#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/app/Application.h"
#include "src/pgplot/PGPLOTController.h"

using namespace app;
using namespace testing;
using namespace pgploti;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
    PGPLOTController::createMock =
        std::make_shared<PGPLOTController::createMockType>();
  }
  ~UTEST_Application() { PGPLOTController::createMock.reset(); }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, normal_exit)
{
  PGPLOTControllerPtr plotter = std::make_shared<PGPLOTController>();

  EXPECT_CALL(*plotter, run(appCtx)).Times(1).WillOnce(Return(true));

  EXPECT_NE(PGPLOTController::createMock, nullptr);
  EXPECT_CALL(*PGPLOTController::createMock, Call())
      .Times(1)
      .WillOnce(Invoke([plotter]() { return plotter; }));

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_Application, plotter_fail_status)
{
  PGPLOTControllerPtr plotter = std::make_shared<PGPLOTController>();

  EXPECT_CALL(*plotter, run(appCtx)).Times(1).WillOnce(Return(false));

  EXPECT_NE(PGPLOTController::createMock, nullptr);
  EXPECT_CALL(*PGPLOTController::createMock, Call())
      .Times(1)
      .WillOnce(Invoke([plotter]() { return plotter; }));

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_NE(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_Application, absent_plotter_instance)
{
  EXPECT_NE(PGPLOTController::createMock, nullptr);
  EXPECT_CALL(*PGPLOTController::createMock, Call())
      .Times(1)
      .WillOnce(Return(PGPLOTControllerPtr{}));

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_NE(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}
