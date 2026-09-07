#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <csignal>

#include "src/app/ApplicationFactory.h"
#include "src/log/log.h"
#include "src/matplotxx/MatPlotxxController.h"

using namespace app;
using namespace testing;
using namespace matplotxxi;

class CTEST_app : public Test
{
 public:
  CTEST_app()
  {
    MatPlotxxController::mock_create =
        std::make_shared<MatPlotxxController::createMockType>();
  }
  virtual ~CTEST_app() { MatPlotxxController::mock_create.reset(); }

  int argc{0};
  char** argv{nullptr};

  ApplicationFactory facade;
};

TEST_F(CTEST_app, create_default_context_success)
{
  auto actx = facade.create_default_context(argc, argv);

  EXPECT_NE(actx, nullptr);
}

TEST_F(CTEST_app, create_default_arg_parser_success)
{
  auto argp = facade.create_default_arg_parser();

  EXPECT_NE(argp, nullptr);
}

TEST_F(CTEST_app, create_default_signals_handler_success)
{
  auto shandler = facade.create_default_signals_handler();

  EXPECT_NE(shandler, nullptr);
}

TEST_F(CTEST_app, create_default_application_success)
{
  auto dapp = facade.create_default_application();

  EXPECT_NE(dapp, nullptr);
}

TEST_F(CTEST_app, create_help_printer_success)
{
  auto hpapp = facade.create_help_printer();

  EXPECT_NE(hpapp, nullptr);
}

TEST_F(CTEST_app, create_context_success)
{
  auto ctx = facade.create_context(argc, argv);

  EXPECT_NE(ctx, nullptr);
}

TEST_F(CTEST_app, create_application_success)
{
  auto actx = facade.create_default_context(argc, argv);

  EXPECT_NE(actx, nullptr);

  auto app = facade.create_application(actx);

  EXPECT_NE(app, nullptr);
}

TEST_F(CTEST_app, signals_handler_stops_the_context)
{
  auto actx = facade.create_default_context(argc, argv);
  auto shandler = facade.create_default_signals_handler();

  EXPECT_TRUE(shandler->install(actx));
  EXPECT_FALSE(actx->get_stop());

  std::raise(SIGTERM);

  // False positive: the raise does return, since the installed handler
  // does return too.
  // cppcheck-suppress unreachableCode
  EXPECT_TRUE(actx->get_stop());
}

TEST_F(CTEST_app, execute_success)
{
  MatPlotxxControllerPtr plotterInstance =
      std::make_shared<MatPlotxxController>();

  EXPECT_CALL(*plotterInstance, run(_)).Times(1).WillOnce(Return(true));
  EXPECT_NE(MatPlotxxController::mock_create, nullptr);
  EXPECT_CALL(*MatPlotxxController::mock_create, Call)
      .Times(1)
      .WillOnce(Invoke([&plotterInstance]() { return plotterInstance; }));

  int status = ApplicationFactory::execute(argc, argv);

  EXPECT_EQ(status, 0);
}

TEST_F(CTEST_app, plotter_signals_fail_status)
{
  MatPlotxxControllerPtr plotterInstance =
      std::make_shared<MatPlotxxController>();

  EXPECT_CALL(*plotterInstance, run(_)).Times(1).WillOnce(Return(false));
  EXPECT_NE(MatPlotxxController::mock_create, nullptr);
  EXPECT_CALL(*MatPlotxxController::mock_create, Call)
      .Times(1)
      .WillOnce(Invoke([&plotterInstance]() { return plotterInstance; }));

  int status = ApplicationFactory::execute(argc, argv);

  EXPECT_NE(status, 0);
}

TEST_F(CTEST_app, no_plotter_instance)
{
  EXPECT_NE(MatPlotxxController::mock_create, nullptr);
  EXPECT_CALL(*MatPlotxxController::mock_create, Call)
      .Times(1)
      .WillOnce(Invoke([]() { return MatPlotxxControllerPtr{}; }));

  int status = ApplicationFactory::execute(argc, argv);

  EXPECT_NE(status, 0);
}
