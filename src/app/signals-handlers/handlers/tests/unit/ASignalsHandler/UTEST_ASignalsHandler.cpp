#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <atomic>
#include <csignal>
#include <memory>
#include <set>

#include "src/app/signals-handlers/handlers/ASignalsHandler.h"

using namespace app;
using namespace testing;

/**
 * @brief A concrete ASignalsHandler descendant which lets the test cases
 * choose the covered signals, the handling routine and to count its calls.
 */
class TestSignalsHandler : public ASignalsHandler
{
 public:
  ~TestSignalsHandler() override { TestSignalsHandler::uninstall(); }
  TestSignalsHandler() = default;

  /// @brief The covered signals of the current test case.
  inline static std::set<int> handledSignals{SIGINT};

  /// @brief The routine of the current test case, set by the
  /// TestSignalsHandler::reset method, since the routine itself is declared
  /// below.
  inline static SignalDisposition signalDisposition{nullptr};

  /// @brief The context the TestSignalsHandler::touch_context routine touches.
  inline static std::atomic<ApplicationContext*> handledContext{nullptr};

  /// @brief The TestSignalsHandler::touch_context calls count.
  inline static std::atomic_int touchesCount{0};

  static void touch_context([[maybe_unused]] int signalNumber)
  {
    touchesCount.fetch_add(1);

    ApplicationContext* const ctx = handledContext.load();

    if (ctx != nullptr) {
      ctx->set_stop(true);
    }
  }

  static void reset_the_state()
  {
    handledSignals = {SIGINT};
    signalDisposition = &TestSignalsHandler::touch_context;
    handledContext.store(nullptr);
    touchesCount.store(0);
  }

  // The overrides are the public ones here, so the test cases reach them.
  virtual const std::set<int>& get_handled_signals() override
  {
    return handledSignals;
  }

  virtual SignalDisposition get_signal_disposition() override
  {
    return signalDisposition;
  }

  virtual void store_context(ApplicationContext* ctx) override
  {
    handledContext.store(ctx);
  }
};

class UTEST_ASignalsHandler : public Test
{
 public:
  UTEST_ASignalsHandler()
      : handler{std::make_shared<TestSignalsHandler>()},
        appCtx{create_context()}
  {
    TestSignalsHandler::reset_the_state();
  }

  ~UTEST_ASignalsHandler() override
  {
    handler.reset();
    TestSignalsHandler::reset_the_state();
  }

  std::shared_ptr<ApplicationContext> create_context()
  {
    return std::make_shared<ApplicationContext>(argc, argv);
  }

  static void expect_the_default_dispositions()
  {
    for (const int signalNumber : TestSignalsHandler::handledSignals) {
      EXPECT_EQ(std::signal(signalNumber, SIG_DFL), SIG_DFL);
    }
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<TestSignalsHandler> handler;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_ASignalsHandler, no_context_error)
{
  EXPECT_FALSE(handler->install({}));

  EXPECT_EQ(TestSignalsHandler::handledContext.load(), nullptr);

  expect_the_default_dispositions();
}

TEST_F(UTEST_ASignalsHandler, no_handler_routine_error)
{
  TestSignalsHandler::signalDisposition = nullptr;

  EXPECT_FALSE(handler->install(appCtx));

  EXPECT_EQ(TestSignalsHandler::handledContext.load(), nullptr);

  expect_the_default_dispositions();
}

TEST_F(UTEST_ASignalsHandler, an_empty_signals_category_is_not_installed)
{
  TestSignalsHandler::handledSignals.clear();

  EXPECT_FALSE(handler->install(appCtx));

  EXPECT_EQ(TestSignalsHandler::handledContext.load(), nullptr);
}

TEST_F(UTEST_ASignalsHandler, install_remembers_the_context)
{
  EXPECT_TRUE(handler->install(appCtx));

  EXPECT_EQ(TestSignalsHandler::handledContext.load(), appCtx.get());
}

TEST_F(UTEST_ASignalsHandler, the_routine_is_called_on_every_covered_signal)
{
  TestSignalsHandler::handledSignals = {SIGINT, SIGTERM};

  EXPECT_TRUE(handler->install(appCtx));

  for (const int signalNumber : TestSignalsHandler::handledSignals) {
    std::raise(signalNumber);
  }

  EXPECT_EQ(TestSignalsHandler::touchesCount.load(), 2);
  EXPECT_TRUE(appCtx->get_stop());
}

TEST_F(UTEST_ASignalsHandler, install_replaces_the_previous_context)
{
  EXPECT_TRUE(handler->install(appCtx));

  std::shared_ptr<ApplicationContext> anotherCtx = create_context();

  EXPECT_TRUE(handler->install(anotherCtx));

  EXPECT_EQ(TestSignalsHandler::handledContext.load(), anotherCtx.get());

  std::raise(SIGINT);

  // cppcheck-suppress unreachableCode
  EXPECT_TRUE(anotherCtx->get_stop());
  EXPECT_FALSE(appCtx->get_stop());
}

TEST_F(UTEST_ASignalsHandler, uninstall_restores_the_default_dispositions)
{
  EXPECT_TRUE(handler->install(appCtx));

  handler->uninstall();

  EXPECT_EQ(TestSignalsHandler::handledContext.load(), nullptr);

  expect_the_default_dispositions();
}

TEST_F(UTEST_ASignalsHandler, the_repeated_uninstall_is_harmless)
{
  EXPECT_TRUE(handler->install(appCtx));

  handler->uninstall();
  handler->uninstall();

  expect_the_default_dispositions();
}

TEST_F(UTEST_ASignalsHandler, the_descendant_destructor_releases_the_signals)
{
  {
    TestSignalsHandler scopedHandler;

    EXPECT_TRUE(scopedHandler.install(appCtx));
  }

  EXPECT_EQ(TestSignalsHandler::handledContext.load(), nullptr);

  expect_the_default_dispositions();
}
