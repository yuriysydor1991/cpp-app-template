#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <csignal>
#include <memory>

#include "src/app/signals-handlers/handlers/posix/IgnoredSignalsHandler.h"

using namespace app;
using namespace testing;

/// @brief Exposes the protected members to the test cases.
class TestIgnoredSignalsHandler : public IgnoredSignalsHandler
{
 public:
  using IgnoredSignalsHandler::get_handled_signals;
  using IgnoredSignalsHandler::get_signal_disposition;
  using IgnoredSignalsHandler::store_context;
};

class UTEST_IgnoredSignalsHandler : public Test
{
 public:
  UTEST_IgnoredSignalsHandler()
      : handler{std::make_shared<TestIgnoredSignalsHandler>()},
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

  std::shared_ptr<TestIgnoredSignalsHandler> handler;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_IgnoredSignalsHandler, the_handler_belongs_to_the_posix_family)
{
  EXPECT_NE(dynamic_cast<PosixSignalsHandler*>(handler.get()), nullptr);
  EXPECT_NE(dynamic_cast<ASignalsHandler*>(handler.get()), nullptr);
  EXPECT_NE(dynamic_cast<ISignalsHandler*>(handler.get()), nullptr);
}

TEST_F(UTEST_IgnoredSignalsHandler, the_broken_pipe_signal_is_covered)
{
#ifdef SIGPIPE
  EXPECT_EQ(handler->get_handled_signals().count(SIGPIPE), 1U);
#endif  // SIGPIPE

  EXPECT_EQ(handler->get_handled_signals().count(SIGINT), 0U);
  EXPECT_EQ(handler->get_handled_signals().count(SIGTERM), 0U);
}

TEST_F(UTEST_IgnoredSignalsHandler, the_ignore_disposition_is_provided)
{
  EXPECT_EQ(handler->get_signal_disposition(), SIG_IGN);

  // The SIG_DFL value equals a nullptr one, which the install method rejects,
  // so the ignoring disposition must not be mistaken for it.
  EXPECT_NE(handler->get_signal_disposition(), SIG_DFL);
  EXPECT_NE(handler->get_signal_disposition(), nullptr);
}

TEST_F(UTEST_IgnoredSignalsHandler, no_context_error)
{
  EXPECT_FALSE(handler->install({}));

  expect_the_default_dispositions();
}

TEST_F(UTEST_IgnoredSignalsHandler, install_success)
{
  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_TRUE(handler->install(appCtx));
}

TEST_F(UTEST_IgnoredSignalsHandler, every_covered_signal_is_ignored)
{
  EXPECT_TRUE(handler->install(appCtx));

  for (const int signalNumber : handler->get_handled_signals()) {
    // The process would be terminated by the OS default disposition here.
    std::raise(signalNumber);
  }

  EXPECT_FALSE(appCtx->get_stop());
  EXPECT_FALSE(appCtx->get_pause());
  EXPECT_FALSE(appCtx->get_reload());
  EXPECT_FALSE(appCtx->get_first_user_request());
  EXPECT_FALSE(appCtx->get_second_user_request());
}

TEST_F(UTEST_IgnoredSignalsHandler, the_context_is_never_kept)
{
  EXPECT_TRUE(handler->install(appCtx));

  // The empty store_context override touches nothing at all, so calling it
  // with any pointer stays harmless.
  handler->store_context(appCtx.get());

  EXPECT_FALSE(appCtx->get_stop());
  EXPECT_FALSE(appCtx->get_pause());
}

TEST_F(UTEST_IgnoredSignalsHandler, uninstall_restores_the_default_dispositions)
{
  EXPECT_TRUE(handler->install(appCtx));

  handler->uninstall();

  expect_the_default_dispositions();
}

TEST_F(UTEST_IgnoredSignalsHandler,
       the_destructor_restores_the_default_dispositions)
{
  {
    TestIgnoredSignalsHandler scopedHandler;

    EXPECT_TRUE(scopedHandler.install(appCtx));
  }

  expect_the_default_dispositions();
}
