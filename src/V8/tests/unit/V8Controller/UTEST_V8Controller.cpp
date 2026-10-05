#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/V8/V8Console.h"
#include "src/V8/V8Controller.h"

using namespace v8i;
using namespace testing;

class UTEST_V8Controller : public Test
{
 public:
  UTEST_V8Controller()
  {
    ON_CALL(installMock, Call()).WillByDefault(Return(true));

    V8Console::onInstall = installMock.AsStdFunction();
  }

  ~UTEST_V8Controller() override { V8Console::onInstall = nullptr; }

  inline static const std::string NAME{"unit.js"};

  NiceMock<MockFunction<bool()>> installMock;
  V8Controller controller;
};

TEST_F(UTEST_V8Controller, create_returns_an_instance)
{
  EXPECT_NE(V8Controller::create(), nullptr);
}

TEST_F(UTEST_V8Controller, run_before_init_fails)
{
  EXPECT_FALSE(controller.run("1 + 2", NAME).has_value());
}

TEST_F(UTEST_V8Controller, init_installs_the_console_once)
{
  EXPECT_CALL(installMock, Call()).Times(1);

  EXPECT_TRUE(controller.init({}));
  EXPECT_TRUE(controller.init({}));
}

TEST_F(UTEST_V8Controller, failed_console_install_fails_the_init)
{
  EXPECT_CALL(installMock, Call())
      .WillOnce(Return(false))
      .WillOnce(Return(true));

  EXPECT_FALSE(controller.init({}));
  EXPECT_FALSE(controller.run("1 + 2", NAME).has_value());

  // The failed init leaves nothing half done behind, so it is retried.
  EXPECT_TRUE(controller.init({}));
  EXPECT_EQ(controller.run("1 + 2", NAME), "3");
}

TEST_F(UTEST_V8Controller, run_returns_the_completion_value)
{
  ASSERT_TRUE(controller.init({}));

  EXPECT_EQ(controller.run("1 + 2", NAME), "3");
  EXPECT_EQ(controller.run("'Hello, ' + 'V8!'", NAME), "Hello, V8!");
}

TEST_F(UTEST_V8Controller, failing_code_returns_nothing)
{
  ASSERT_TRUE(controller.init({}));

  EXPECT_FALSE(controller.run("let = ;", NAME).has_value());
  EXPECT_FALSE(controller.run("throw new Error('boom')", NAME).has_value());
}
