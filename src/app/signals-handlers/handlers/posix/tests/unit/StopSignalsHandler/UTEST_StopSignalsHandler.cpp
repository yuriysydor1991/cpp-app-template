#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <csignal>
#include <memory>

#include "src/app/signals-handlers/handlers/posix/StopSignalsHandler.h"

using namespace app;
using namespace testing;

/// @brief Exposes the protected members to the test cases.
class TestStopSignalsHandler : public StopSignalsHandler
{
 public:
  using StopSignalsHandler::get_handled_signals;
  using StopSignalsHandler::get_signal_disposition;
  using StopSignalsHandler::stop_context;
};

class UTEST_StopSignalsHandler : public Test
{
 public:
  UTEST_StopSignalsHandler()
      : handler{std::make_shared<TestStopSignalsHandler>()},
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

  std::shared_ptr<TestStopSignalsHandler> handler;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_StopSignalsHandler, the_handler_belongs_to_the_posix_family)
{
  EXPECT_NE(dynamic_cast<PosixSignalsHandler*>(handler.get()), nullptr);
  EXPECT_NE(dynamic_cast<ASignalsHandler*>(handler.get()), nullptr);
  EXPECT_NE(dynamic_cast<ISignalsHandler*>(handler.get()), nullptr);
}

TEST_F(UTEST_StopSignalsHandler, the_termination_signals_are_covered)
{
  EXPECT_EQ(handler->get_handled_signals().count(SIGINT), 1U);
  EXPECT_EQ(handler->get_handled_signals().count(SIGTERM), 1U);

  // The SIGHUP one belongs to the ReloadSignalsHandler category instead.
#ifdef SIGHUP
  EXPECT_EQ(handler->get_handled_signals().count(SIGHUP), 0U);
#endif  // SIGHUP

#ifdef SIGTSTP
  EXPECT_EQ(handler->get_handled_signals().count(SIGTSTP), 0U);
#endif  // SIGTSTP
#ifdef SIGCONT
  EXPECT_EQ(handler->get_handled_signals().count(SIGCONT), 0U);
#endif  // SIGCONT
#ifdef SIGSTOP
  EXPECT_EQ(handler->get_handled_signals().count(SIGSTOP), 0U);
#endif  // SIGSTOP
}

TEST_F(UTEST_StopSignalsHandler, the_own_routine_is_provided)
{
  EXPECT_EQ(handler->get_signal_disposition(),
            &TestStopSignalsHandler::stop_context);
}

TEST_F(UTEST_StopSignalsHandler, no_context_error)
{
  EXPECT_FALSE(handler->install({}));

  expect_the_default_dispositions();
}

TEST_F(UTEST_StopSignalsHandler, install_success)
{
  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_TRUE(handler->install(appCtx));

  EXPECT_FALSE(appCtx->get_stop());
  EXPECT_FALSE(appCtx->get_pause());
}

TEST_F(UTEST_StopSignalsHandler, every_covered_signal_stops_the_context)
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
    EXPECT_FALSE(signalCtx->get_pause());
  }
}

TEST_F(UTEST_StopSignalsHandler, uninstall_restores_the_default_dispositions)
{
  EXPECT_TRUE(handler->install(appCtx));

  handler->uninstall();

  expect_the_default_dispositions();
}

TEST_F(UTEST_StopSignalsHandler,
       the_destructor_restores_the_default_dispositions)
{
  {
    TestStopSignalsHandler scopedHandler;

    EXPECT_TRUE(scopedHandler.install(appCtx));
  }

  expect_the_default_dispositions();
}

TEST_F(UTEST_StopSignalsHandler, the_released_context_stays_untouched)
{
  EXPECT_TRUE(handler->install(appCtx));

  handler->uninstall();

  TestStopSignalsHandler::stop_context(SIGINT);

  EXPECT_FALSE(appCtx->get_stop());
  EXPECT_FALSE(appCtx->get_pause());
}
