#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <csignal>
#include <memory>

#include "src/app/signals-handlers/handlers/posix/ContinueSignalsHandler.h"

using namespace app;
using namespace testing;

/// @brief Exposes the protected members to the test cases.
class TestContinueSignalsHandler : public ContinueSignalsHandler
{
 public:
  using ContinueSignalsHandler::continue_context;
  using ContinueSignalsHandler::get_handled_signals;
  using ContinueSignalsHandler::get_signal_disposition;
};

class UTEST_ContinueSignalsHandler : public Test
{
 public:
  UTEST_ContinueSignalsHandler()
      : handler{std::make_shared<TestContinueSignalsHandler>()},
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

  std::shared_ptr<TestContinueSignalsHandler> handler;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_ContinueSignalsHandler, the_handler_belongs_to_the_posix_family)
{
  EXPECT_NE(dynamic_cast<PosixSignalsHandler*>(handler.get()), nullptr);
  EXPECT_NE(dynamic_cast<ASignalsHandler*>(handler.get()), nullptr);
  EXPECT_NE(dynamic_cast<ISignalsHandler*>(handler.get()), nullptr);
}

TEST_F(UTEST_ContinueSignalsHandler, the_continue_signal_is_covered)
{
#ifdef SIGCONT
  EXPECT_EQ(handler->get_handled_signals().count(SIGCONT), 1U);
#endif  // SIGCONT

  EXPECT_EQ(handler->get_handled_signals().count(SIGINT), 0U);
  EXPECT_EQ(handler->get_handled_signals().count(SIGTERM), 0U);

#ifdef SIGTSTP
  EXPECT_EQ(handler->get_handled_signals().count(SIGTSTP), 0U);
#endif  // SIGTSTP
}

TEST_F(UTEST_ContinueSignalsHandler, the_own_routine_is_provided)
{
  EXPECT_EQ(handler->get_signal_disposition(),
            &TestContinueSignalsHandler::continue_context);
}

TEST_F(UTEST_ContinueSignalsHandler, no_context_error)
{
  EXPECT_FALSE(handler->install({}));

  expect_the_default_dispositions();
}

TEST_F(UTEST_ContinueSignalsHandler, install_success)
{
  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_TRUE(handler->install(appCtx));

  EXPECT_FALSE(appCtx->get_pause());
  EXPECT_FALSE(appCtx->get_stop());
}

TEST_F(UTEST_ContinueSignalsHandler, every_covered_signal_resumes_the_context)
{
  for (const int signalNumber : handler->get_handled_signals()) {
    std::shared_ptr<ApplicationContext> signalCtx = create_context();

    EXPECT_TRUE(handler->install(signalCtx));

    signalCtx->set_pause(true);

    std::raise(signalNumber);

    // False positive: the raise does return, since the installed handler
    // does return too.
    // cppcheck-suppress unreachableCode
    EXPECT_FALSE(signalCtx->get_pause());
    EXPECT_FALSE(signalCtx->get_stop());
  }
}

TEST_F(UTEST_ContinueSignalsHandler,
       uninstall_restores_the_default_dispositions)
{
  EXPECT_TRUE(handler->install(appCtx));

  handler->uninstall();

  expect_the_default_dispositions();
}

TEST_F(UTEST_ContinueSignalsHandler,
       the_destructor_restores_the_default_dispositions)
{
  {
    TestContinueSignalsHandler scopedHandler;

    EXPECT_TRUE(scopedHandler.install(appCtx));
  }

  expect_the_default_dispositions();
}

TEST_F(UTEST_ContinueSignalsHandler, the_released_context_stays_untouched)
{
  EXPECT_TRUE(handler->install(appCtx));

  handler->uninstall();

  appCtx->set_pause(true);

  TestContinueSignalsHandler::continue_context(SIGINT);

  EXPECT_TRUE(appCtx->get_pause());
}
