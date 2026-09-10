#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <csignal>
#include <memory>

#include "src/app/signals-handlers/handlers/posix/ReloadSignalsHandler.h"

using namespace app;
using namespace testing;

/// @brief Exposes the protected members to the test cases.
class TestReloadSignalsHandler : public ReloadSignalsHandler
{
 public:
  using ReloadSignalsHandler::get_handled_signals;
  using ReloadSignalsHandler::get_signal_disposition;
  using ReloadSignalsHandler::reload_context;
};

class UTEST_ReloadSignalsHandler : public Test
{
 public:
  UTEST_ReloadSignalsHandler()
      : handler{std::make_shared<TestReloadSignalsHandler>()},
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

  std::shared_ptr<TestReloadSignalsHandler> handler;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_ReloadSignalsHandler, the_handler_belongs_to_the_posix_family)
{
  EXPECT_NE(dynamic_cast<PosixSignalsHandler*>(handler.get()), nullptr);
  EXPECT_NE(dynamic_cast<ASignalsHandler*>(handler.get()), nullptr);
  EXPECT_NE(dynamic_cast<ISignalsHandler*>(handler.get()), nullptr);
}

TEST_F(UTEST_ReloadSignalsHandler, the_hangup_signal_is_covered)
{
#ifdef SIGHUP
  EXPECT_EQ(handler->get_handled_signals().count(SIGHUP), 1U);
#endif  // SIGHUP

  EXPECT_EQ(handler->get_handled_signals().count(SIGINT), 0U);
  EXPECT_EQ(handler->get_handled_signals().count(SIGTERM), 0U);
}

TEST_F(UTEST_ReloadSignalsHandler, the_own_routine_is_provided)
{
  EXPECT_EQ(handler->get_signal_disposition(),
            &TestReloadSignalsHandler::reload_context);
}

TEST_F(UTEST_ReloadSignalsHandler, no_context_error)
{
  EXPECT_FALSE(handler->install({}));

  expect_the_default_dispositions();
}

TEST_F(UTEST_ReloadSignalsHandler, install_success)
{
  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_TRUE(handler->install(appCtx));

  EXPECT_FALSE(appCtx->get_reload());
  EXPECT_FALSE(appCtx->get_stop());
}

TEST_F(UTEST_ReloadSignalsHandler, the_hangup_signal_reloads_the_context)
{
#ifdef SIGHUP
  EXPECT_TRUE(handler->install(appCtx));
  EXPECT_FALSE(appCtx->get_reload());

  // The installed handler replaces the OS default disposition, so the current
  // process is not terminated by the raise below.
  std::raise(SIGHUP);

  // False positive: the raise does return, since the installed handler
  // does return too.
  // cppcheck-suppress unreachableCode
  EXPECT_TRUE(appCtx->get_reload());
  EXPECT_FALSE(appCtx->get_stop());
  EXPECT_FALSE(appCtx->get_pause());
#endif  // SIGHUP
}

TEST_F(UTEST_ReloadSignalsHandler, uninstall_restores_the_default_dispositions)
{
  EXPECT_TRUE(handler->install(appCtx));

  handler->uninstall();

  expect_the_default_dispositions();
}

TEST_F(UTEST_ReloadSignalsHandler,
       the_destructor_restores_the_default_dispositions)
{
  {
    TestReloadSignalsHandler scopedHandler;

    EXPECT_TRUE(scopedHandler.install(appCtx));
  }

  expect_the_default_dispositions();
}

TEST_F(UTEST_ReloadSignalsHandler, the_released_context_stays_untouched)
{
  EXPECT_TRUE(handler->install(appCtx));

  handler->uninstall();

  TestReloadSignalsHandler::reload_context(SIGINT);

  EXPECT_FALSE(appCtx->get_reload());
}
