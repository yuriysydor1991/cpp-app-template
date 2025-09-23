#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/app/ApplicationFactory.h"
#include "src/mysqlcppconn/MySQLController.h"

using namespace app;
using namespace testing;
using namespace mysqli;

class CTEST_app : public Test
{
 public:
  CTEST_app() = default;
  ~CTEST_app(){
    MySQLController::onMockCreate = nullptr;
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
  MockFunction<void(MySQLController&)> controllerEnsurer;

  EXPECT_CALL(controllerEnsurer, Call).Times(1).WillOnce(Invoke([](MySQLController& i){
    EXPECT_CALL(i, connect(_)).Times(1).WillOnce(Return(true));
    EXPECT_CALL(i, get_current_date)
            .Times(1)
            .WillOnce(Return(std::string{"2025-09-23"}));
  }));

  MySQLController::onMockCreate = controllerEnsurer.AsStdFunction();

  int status = ApplicationFactory::execute(argc, argv);

  EXPECT_EQ(status, 0);
}

TEST_F(CTEST_app, execute_failure)
{
  MockFunction<void(MySQLController&)> controllerEnsurer;

  EXPECT_CALL(controllerEnsurer, Call).Times(1).WillOnce(Invoke([](MySQLController& i){
    EXPECT_CALL(i, connect(_)).Times(1).WillOnce(Return(false));
    EXPECT_CALL(i, get_current_date)
            .Times(0);
  }));

  MySQLController::onMockCreate = controllerEnsurer.AsStdFunction();

  int status = ApplicationFactory::execute(argc, argv);

  EXPECT_NE(status, 0);
}