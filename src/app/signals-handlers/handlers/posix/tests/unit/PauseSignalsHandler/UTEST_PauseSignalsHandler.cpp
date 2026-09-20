#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <csignal>
#include <memory>

#include "src/app/signals-handlers/handlers/posix/PauseSignalsHandler.h"

using namespace app;
using namespace testing;

/// @brief Exposes the protected members to the test cases.
class TestPauseSignalsHandler : public PauseSignalsHandler
{
 public:
  using PauseSignalsHandler::get_handled_signals;
  using PauseSignalsHandler::get_signal_disposition;
  using PauseSignalsHandler::pause_context;
};

class UTEST_PauseSignalsHandler : public Test
{
 public:
  UTEST_PauseSignalsHandler()
      : handler{std::make_shared<TestPauseSignalsHandler>()},
        appCtx{create_context()}
  {
    restore_the_default_dispositions();
  }

  std::shared_ptr<ApplicationContext> create_context()
  {
    return std::make_shared<ApplicationContext>(argc, argv);
  }

  /// @brief Gives the covered signals the OS default disposition, since a
  /// process inherits the ignored ones of its parent - the nohup tool and the
  /// shell job control do leave some of them ignored.
  void restore_the_default_dispositions()
  {
    for (const int signalNumber : handler->get_handled_signals()) {
      std::signal(signalNumber, SIG_DFL);
    }
  }

  void expect_the_default_dispositions()
  {
    for (const int signalNumber : handler->get_handled_signals()) {
      EXPECT_EQ(std::signal(signalNumber, SIG_DFL), SIG_DFL);
    }
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<TestPauseSignalsHandler> handler;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_PauseSignalsHandler, the_handler_belongs_to_the_posix_family)
{
  EXPECT_NE(dynamic_cast<PosixSignalsHandler*>(handler.get()), nullptr);
  EXPECT_NE(dynamic_cast<ASignalsHandler*>(handler.get()), nullptr);
  EXPECT_NE(dynamic_cast<ISignalsHandler*>(handler.get()), nullptr);
}

TEST_F(UTEST_PauseSignalsHandler, the_suspension_signals_are_covered)
{
#ifdef SIGTSTP
  EXPECT_EQ(handler->get_handled_signals().count(SIGTSTP), 1U);
#endif  // SIGTSTP
#ifdef SIGTTIN
  EXPECT_EQ(handler->get_handled_signals().count(SIGTTIN), 1U);
#endif  // SIGTTIN
#ifdef SIGTTOU
  EXPECT_EQ(handler->get_handled_signals().count(SIGTTOU), 1U);
#endif  // SIGTTOU

  EXPECT_EQ(handler->get_handled_signals().count(SIGINT), 0U);
  EXPECT_EQ(handler->get_handled_signals().count(SIGTERM), 0U);
}

TEST_F(UTEST_PauseSignalsHandler, the_uncatchable_stop_signal_is_not_covered)
{
#ifdef SIGSTOP
  EXPECT_EQ(handler->get_handled_signals().count(SIGSTOP), 0U);
#endif  // SIGSTOP
}

TEST_F(UTEST_PauseSignalsHandler, the_own_routine_is_provided)
{
  EXPECT_EQ(handler->get_signal_disposition(),
            &TestPauseSignalsHandler::pause_context);
}

TEST_F(UTEST_PauseSignalsHandler, no_context_error)
{
  EXPECT_FALSE(handler->install({}));

  expect_the_default_dispositions();
}

TEST_F(UTEST_PauseSignalsHandler, install_success)
{
  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_TRUE(handler->install(appCtx));

  EXPECT_FALSE(appCtx->get_pause());
  EXPECT_FALSE(appCtx->get_stop());
}

TEST_F(UTEST_PauseSignalsHandler, every_covered_signal_pauses_the_context)
{
  for (const int signalNumber : handler->get_handled_signals()) {
    std::shared_ptr<ApplicationContext> signalCtx = create_context();

    EXPECT_TRUE(handler->install(signalCtx));
    EXPECT_FALSE(signalCtx->get_pause());

    // The installed handler replaces the OS default disposition, so the
    // current process is not suspended by the raise below.
    std::raise(signalNumber);

    // False positive: the raise does return, since the installed handler
    // does return too.
    // cppcheck-suppress unreachableCode
    EXPECT_TRUE(signalCtx->get_pause());
    EXPECT_FALSE(signalCtx->get_stop());
  }
}

TEST_F(UTEST_PauseSignalsHandler, uninstall_restores_the_default_dispositions)
{
  EXPECT_TRUE(handler->install(appCtx));

  handler->uninstall();

  expect_the_default_dispositions();
}

TEST_F(UTEST_PauseSignalsHandler,
       the_destructor_restores_the_default_dispositions)
{
  {
    TestPauseSignalsHandler scopedHandler;

    EXPECT_TRUE(scopedHandler.install(appCtx));
  }

  expect_the_default_dispositions();
}

TEST_F(UTEST_PauseSignalsHandler, the_released_context_stays_untouched)
{
  EXPECT_TRUE(handler->install(appCtx));

  handler->uninstall();

  TestPauseSignalsHandler::pause_context(SIGINT);

  EXPECT_FALSE(appCtx->get_pause());
  EXPECT_FALSE(appCtx->get_stop());
}
