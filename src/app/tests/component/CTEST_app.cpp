#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/app/ApplicationFactory.h"
#include "src/plplot/PLplotController.h"

using namespace app;
using namespace testing;
using namespace plploti;

class CTEST_app : public Test
{
 public:
  CTEST_app()
  {
    PLplotController::createMock = std::make_shared<PLplotController::createMockType>();
  }
  ~CTEST_app() {
    PLplotController::createMock.reset();
  }

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

TEST_F(CTEST_app, execute_success)
{
  PLplotControllerPtr plotter = std::make_shared<PLplotController>();

  EXPECT_CALL(*plotter, run(_)).Times(1).WillOnce(Return(true));

  EXPECT_NE(PLplotController::createMock, nullptr);
  EXPECT_CALL(*PLplotController::createMock, Call()).Times(1).WillOnce(
    Invoke([plotter](){
        return plotter;
    })
  );

  int status = ApplicationFactory::execute(argc, argv);

  EXPECT_EQ(status, 0);
}

TEST_F(CTEST_app, plotter_fail_status)
{
  PLplotControllerPtr plotter = std::make_shared<PLplotController>();

  EXPECT_CALL(*plotter, run(_)).Times(1).WillOnce(Return(false));

  EXPECT_NE(PLplotController::createMock, nullptr);
  EXPECT_CALL(*PLplotController::createMock, Call()).Times(1).WillOnce(
    Invoke([plotter](){
        return plotter;
    })
  );

  int status = ApplicationFactory::execute(argc, argv);

  EXPECT_NE(status, 0);
}

TEST_F(CTEST_app, absent_plotter_instance)
{
  EXPECT_NE(PLplotController::createMock, nullptr);
  EXPECT_CALL(*PLplotController::createMock, Call()).Times(1).WillOnce(
    Return(PLplotControllerPtr{})
  );

  int status = ApplicationFactory::execute(argc, argv);

  EXPECT_NE(status, 0);
}
