#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <csignal>
#include <memory>

#include "src/app/signals-handlers/handlers/posix/UserSignalsHandler.h"

using namespace app;
using namespace testing;

/// @brief Exposes the protected members to the test cases.
class TestUserSignalsHandler : public UserSignalsHandler
{
 public:
  using UserSignalsHandler::get_handled_signals;
  using UserSignalsHandler::get_signal_disposition;
  using UserSignalsHandler::request_context;
};

class UTEST_UserSignalsHandler : public Test
{
 public:
  UTEST_UserSignalsHandler()
      : handler{std::make_shared<TestUserSignalsHandler>()},
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

  std::shared_ptr<TestUserSignalsHandler> handler;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_UserSignalsHandler, the_handler_belongs_to_the_posix_family)
{
  EXPECT_NE(dynamic_cast<PosixSignalsHandler*>(handler.get()), nullptr);
  EXPECT_NE(dynamic_cast<ASignalsHandler*>(handler.get()), nullptr);
  EXPECT_NE(dynamic_cast<ISignalsHandler*>(handler.get()), nullptr);
}

TEST_F(UTEST_UserSignalsHandler, the_user_defined_signals_are_covered)
{
#ifdef SIGUSR1
  EXPECT_EQ(handler->get_handled_signals().count(SIGUSR1), 1U);
#endif  // SIGUSR1
#ifdef SIGUSR2
  EXPECT_EQ(handler->get_handled_signals().count(SIGUSR2), 1U);
#endif  // SIGUSR2

  EXPECT_EQ(handler->get_handled_signals().count(SIGINT), 0U);
  EXPECT_EQ(handler->get_handled_signals().count(SIGTERM), 0U);
}

TEST_F(UTEST_UserSignalsHandler, the_own_routine_is_provided)
{
  EXPECT_EQ(handler->get_signal_disposition(),
            &TestUserSignalsHandler::request_context);
}

TEST_F(UTEST_UserSignalsHandler, no_context_error)
{
  EXPECT_FALSE(handler->install({}));

  expect_the_default_dispositions();
}

TEST_F(UTEST_UserSignalsHandler, install_success)
{
  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_TRUE(handler->install(appCtx));

  EXPECT_FALSE(appCtx->get_first_user_request());
  EXPECT_FALSE(appCtx->get_second_user_request());
}

TEST_F(UTEST_UserSignalsHandler, the_first_signal_raises_the_first_request)
{
#ifdef SIGUSR1
  EXPECT_TRUE(handler->install(appCtx));

  std::raise(SIGUSR1);

  // False positive: the raise does return, since the installed handler
  // does return too.
  // cppcheck-suppress unreachableCode
  EXPECT_TRUE(appCtx->get_first_user_request());
  EXPECT_FALSE(appCtx->get_second_user_request());

  EXPECT_FALSE(appCtx->get_stop());
  EXPECT_FALSE(appCtx->get_pause());
  EXPECT_FALSE(appCtx->get_reload());
#endif  // SIGUSR1
}

TEST_F(UTEST_UserSignalsHandler, the_second_signal_raises_the_second_request)
{
#ifdef SIGUSR2
  EXPECT_TRUE(handler->install(appCtx));

  std::raise(SIGUSR2);

  // cppcheck-suppress unreachableCode
  EXPECT_TRUE(appCtx->get_second_user_request());
  EXPECT_FALSE(appCtx->get_first_user_request());
#endif  // SIGUSR2
}

TEST_F(UTEST_UserSignalsHandler, the_requests_coalesce)
{
#ifdef SIGUSR1
  EXPECT_TRUE(handler->install(appCtx));

  std::raise(SIGUSR1);

  // False positive: the raise does return, since the installed handler
  // does return too.
  // cppcheck-suppress unreachableCode
  std::raise(SIGUSR1);

  EXPECT_TRUE(appCtx->get_first_user_request());

  // The application lowers the served request on its own.
  appCtx->set_first_user_request(false);

  EXPECT_FALSE(appCtx->get_first_user_request());

  std::raise(SIGUSR1);

  EXPECT_TRUE(appCtx->get_first_user_request());
#endif  // SIGUSR1
}

TEST_F(UTEST_UserSignalsHandler, an_alien_signal_number_raises_nothing)
{
  EXPECT_TRUE(handler->install(appCtx));

  TestUserSignalsHandler::request_context(SIGINT);

  EXPECT_FALSE(appCtx->get_first_user_request());
  EXPECT_FALSE(appCtx->get_second_user_request());
}

TEST_F(UTEST_UserSignalsHandler, uninstall_restores_the_default_dispositions)
{
  EXPECT_TRUE(handler->install(appCtx));

  handler->uninstall();

  expect_the_default_dispositions();
}

TEST_F(UTEST_UserSignalsHandler,
       the_destructor_restores_the_default_dispositions)
{
  {
    TestUserSignalsHandler scopedHandler;

    EXPECT_TRUE(scopedHandler.install(appCtx));
  }

  expect_the_default_dispositions();
}

TEST_F(UTEST_UserSignalsHandler, the_released_context_stays_untouched)
{
  EXPECT_TRUE(handler->install(appCtx));

  handler->uninstall();

#ifdef SIGUSR1
  TestUserSignalsHandler::request_context(SIGUSR1);
#endif  // SIGUSR1

  EXPECT_FALSE(appCtx->get_first_user_request());
  EXPECT_FALSE(appCtx->get_second_user_request());
}
