#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <csignal>
#include <memory>

#include "src/app/signals-handlers/SignalsHandler.h"

using namespace app;
using namespace testing;

/// @brief Exposes the protected members to the test cases.
class TestSignalsHandler : public SignalsHandler
{
 public:
  using SignalsHandler::get_handled_signals;
  using SignalsHandler::stop_context;
};

class UTEST_SignalsHandler : public Test
{
 public:
  UTEST_SignalsHandler()
      : handler{std::make_shared<TestSignalsHandler>()},
        appCtx{create_context()}
  {
  }

  std::shared_ptr<ApplicationContext> create_context()
  {
    return std::make_shared<ApplicationContext>(argc, argv);
  }

  void expect_the_default_dispositions()
  {
    for (const int signalNumber : handler->get_handled_signals()) {
      EXPECT_EQ(std::signal(signalNumber, SIG_DFL), SIG_DFL);
    }
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<TestSignalsHandler> handler;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_SignalsHandler, no_context_error)
{
  EXPECT_FALSE(handler->install({}));

  expect_the_default_dispositions();
}

TEST_F(UTEST_SignalsHandler, install_success)
{
  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_TRUE(handler->install(appCtx));

  EXPECT_FALSE(appCtx->get_stop());
}

TEST_F(UTEST_SignalsHandler, every_handled_signal_stops_the_context)
{
  for (const int signalNumber : handler->get_handled_signals()) {
    std::shared_ptr<ApplicationContext> signalCtx = create_context();

    EXPECT_TRUE(handler->install(signalCtx));
    EXPECT_FALSE(signalCtx->get_stop());

    std::raise(signalNumber);

    // False positive: the raise does return, since the installed handler
    // does return too.
    // cppcheck-suppress unreachableCode
    EXPECT_TRUE(signalCtx->get_stop());
  }
}

TEST_F(UTEST_SignalsHandler, uninstall_restores_the_default_dispositions)
{
  EXPECT_TRUE(handler->install(appCtx));

  handler->uninstall();

  expect_the_default_dispositions();
}

TEST_F(UTEST_SignalsHandler, the_destructor_restores_the_default_dispositions)
{
  {
    TestSignalsHandler scopedHandler;

    EXPECT_TRUE(scopedHandler.install(appCtx));
  }

  expect_the_default_dispositions();
}

TEST_F(UTEST_SignalsHandler, the_released_context_stays_untouched)
{
  EXPECT_TRUE(handler->install(appCtx));

  handler->uninstall();

  TestSignalsHandler::stop_context(SIGINT);

  EXPECT_FALSE(appCtx->get_stop());
}
