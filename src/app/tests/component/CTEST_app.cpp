#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/app/ApplicationFactory.h"
#include "src/beasthttp/HttpController.h"

using namespace app;
using namespace testing;
using namespace beasthttp;

class CTEST_app : public Test
{
 public:
  CTEST_app() = default;
  ~CTEST_app() {
    HttpController::onMockCreate = nullptr;
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
  testing::MockFunction<void(HttpController&)> httpEnsurer;

  EXPECT_CALL(httpEnsurer, Call).Times(1).WillOnce(
    testing::Invoke(
      [](HttpController& http){
        EXPECT_CALL(http, serve).Times(1).WillOnce(testing::Return(true));
      }
    )
  );

  HttpController::onMockCreate = httpEnsurer.AsStdFunction();
  
  int status = ApplicationFactory::execute(argc, argv);

  EXPECT_EQ(status, 0);
}

TEST_F(CTEST_app, execute_http_controller_failure)
{
  testing::MockFunction<void(HttpController&)> httpEnsurer;

  EXPECT_CALL(httpEnsurer, Call).Times(1).WillOnce(
    testing::Invoke(
      [](HttpController& http){
        EXPECT_CALL(http, serve).Times(1).WillOnce(testing::Return(false));
      }
    )
  );

  HttpController::onMockCreate = httpEnsurer.AsStdFunction();
  
  int status = ApplicationFactory::execute(argc, argv);

  EXPECT_NE(status, 0);
}
