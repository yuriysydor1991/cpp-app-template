#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <memory>
#include <vector>

#include "src/app/signals-handlers/SignalsHandler.h"
#include "src/app/signals-handlers/handlers/posix/ContinueSignalsHandler.h"
#include "src/app/signals-handlers/handlers/posix/IgnoredSignalsHandler.h"
#include "src/app/signals-handlers/handlers/posix/PauseSignalsHandler.h"
#include "src/app/signals-handlers/handlers/posix/ReloadSignalsHandler.h"
#include "src/app/signals-handlers/handlers/posix/StopSignalsHandler.h"
#include "src/app/signals-handlers/handlers/posix/UserSignalsHandler.h"

using namespace app;
using namespace testing;

/// @brief Exposes the protected members to the test cases.
class TestSignalsHandler : public SignalsHandler
{
 public:
  using SignalsHandler::create_handlers;
};

class UTEST_SignalsHandler : public Test
{
 public:
  /// @brief The signals categories the facade is expected to cover.
  static constexpr const int expectedSubhandlers{6};

  UTEST_SignalsHandler()
      : handler{std::make_shared<TestSignalsHandler>()},
        appCtx{create_context()}
  {
  }

  ~UTEST_SignalsHandler() override
  {
    handler.reset();

    forget_the_hooks();
  }

  std::shared_ptr<ApplicationContext> create_context()
  {
    return std::make_shared<ApplicationContext>(argc, argv);
  }

  /**
   * @brief Makes every created subhandler mock of the given category counted
   * and expecting a single install call with the fixture context.
   *
   * @tparam SubhandlerType The subhandler mock class to hook.
   * @param installResult The value the install call of the category returns.
   * @param uninstallTimes The expected uninstall calls count of the category.
   */
  template <typename SubhandlerType>
  void hook_the_category(const bool installResult,
                         const Cardinality& uninstallTimes)
  {
    SubhandlerType::onMockCreate = [this, installResult,
                                    uninstallTimes](SubhandlerType& instance) {
      ++createdSubhandlers;

      EXPECT_CALL(instance, install(Eq(appCtx)))
          .Times(1)
          .WillOnce(Return(installResult));

      EXPECT_CALL(instance, uninstall()).Times(uninstallTimes);
    };
  }

  /// @brief Makes every created subhandler mock counted only, without
  /// expecting any call of it.
  template <typename SubhandlerType>
  void count_the_category()
  {
    SubhandlerType::onMockCreate = [this](SubhandlerType&) {
      ++createdSubhandlers;
    };
  }

  /// @brief Hooks every covered category at once. See the
  /// UTEST_SignalsHandler::hook_the_category method.
  void hook_the_subhandlers(const bool installResult,
                            const Cardinality& uninstallTimes)
  {
    hook_the_category<StopSignalsHandler>(installResult, uninstallTimes);
    hook_the_category<PauseSignalsHandler>(installResult, uninstallTimes);
    hook_the_category<ContinueSignalsHandler>(installResult, uninstallTimes);
    hook_the_category<ReloadSignalsHandler>(installResult, uninstallTimes);
    hook_the_category<UserSignalsHandler>(installResult, uninstallTimes);
    hook_the_category<IgnoredSignalsHandler>(installResult, uninstallTimes);
  }

  /**
   * @brief Counts the created subhandlers of the given category.
   *
   * @tparam SubhandlerType The subhandler mock class to look for.
   * @param subhandlers The created subhandlers to look through.
   */
  template <typename SubhandlerType>
  static int count_of(
      const std::vector<std::shared_ptr<ISignalsHandler>>& subhandlers)
  {
    return static_cast<int>(std::count_if(
        subhandlers.begin(), subhandlers.end(),
        [](const std::shared_ptr<ISignalsHandler>& subhandler) {
          return std::dynamic_pointer_cast<SubhandlerType>(subhandler) !=
                 nullptr;
        }));
  }

  /// @brief Counts every covered category without expecting any call.
  void count_the_subhandlers()
  {
    count_the_category<StopSignalsHandler>();
    count_the_category<PauseSignalsHandler>();
    count_the_category<ContinueSignalsHandler>();
    count_the_category<ReloadSignalsHandler>();
    count_the_category<UserSignalsHandler>();
    count_the_category<IgnoredSignalsHandler>();
  }

  static void forget_the_hooks()
  {
    StopSignalsHandler::onMockCreate = nullptr;
    PauseSignalsHandler::onMockCreate = nullptr;
    ContinueSignalsHandler::onMockCreate = nullptr;
    ReloadSignalsHandler::onMockCreate = nullptr;
    UserSignalsHandler::onMockCreate = nullptr;
    IgnoredSignalsHandler::onMockCreate = nullptr;
  }

  int argc{0};
  char** argv{nullptr};

  int createdSubhandlers{0};

  std::shared_ptr<TestSignalsHandler> handler;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_SignalsHandler, no_context_error)
{
  hook_the_subhandlers(true, Exactly(0));

  EXPECT_FALSE(handler->install({}));

  EXPECT_EQ(createdSubhandlers, 0);
}

TEST_F(UTEST_SignalsHandler, every_signals_category_is_covered)
{
  count_the_subhandlers();

  const std::vector<std::shared_ptr<ISignalsHandler>> subhandlers =
      handler->create_handlers();

  EXPECT_EQ(subhandlers.size(), static_cast<size_t>(expectedSubhandlers));
  EXPECT_EQ(createdSubhandlers, expectedSubhandlers);

  for (const std::shared_ptr<ISignalsHandler>& subhandler : subhandlers) {
    EXPECT_NE(subhandler, nullptr);
  }
}

TEST_F(UTEST_SignalsHandler, the_created_subhandlers_are_the_expected_ones)
{
  const std::vector<std::shared_ptr<ISignalsHandler>> subhandlers =
      handler->create_handlers();

  EXPECT_EQ(count_of<StopSignalsHandler>(subhandlers), 1);
  EXPECT_EQ(count_of<PauseSignalsHandler>(subhandlers), 1);
  EXPECT_EQ(count_of<ContinueSignalsHandler>(subhandlers), 1);
  EXPECT_EQ(count_of<ReloadSignalsHandler>(subhandlers), 1);
  EXPECT_EQ(count_of<UserSignalsHandler>(subhandlers), 1);
  EXPECT_EQ(count_of<IgnoredSignalsHandler>(subhandlers), 1);
}

TEST_F(UTEST_SignalsHandler, install_reaches_every_subhandler)
{
  hook_the_subhandlers(true, AnyNumber());

  EXPECT_TRUE(handler->install(appCtx));

  EXPECT_EQ(createdSubhandlers, expectedSubhandlers);
}

TEST_F(UTEST_SignalsHandler, install_fails_when_no_subhandler_covers_a_signal)
{
  hook_the_subhandlers(false, AnyNumber());

  EXPECT_FALSE(handler->install(appCtx));

  EXPECT_EQ(createdSubhandlers, expectedSubhandlers);
}

TEST_F(UTEST_SignalsHandler, a_single_covering_subhandler_is_enough)
{
  hook_the_subhandlers(false, AnyNumber());

  // A category which covers no signal on the current platform is not an error
  // of the facade on its own.
  hook_the_category<PauseSignalsHandler>(true, AnyNumber());

  EXPECT_TRUE(handler->install(appCtx));

  EXPECT_EQ(createdSubhandlers, expectedSubhandlers);
}

TEST_F(UTEST_SignalsHandler, uninstall_reaches_every_subhandler)
{
  hook_the_subhandlers(true, Exactly(1));

  EXPECT_TRUE(handler->install(appCtx));

  handler->uninstall();

  EXPECT_EQ(createdSubhandlers, expectedSubhandlers);
}

TEST_F(UTEST_SignalsHandler, the_repeated_uninstall_is_harmless)
{
  hook_the_subhandlers(true, Exactly(1));

  EXPECT_TRUE(handler->install(appCtx));

  handler->uninstall();
  handler->uninstall();

  EXPECT_EQ(createdSubhandlers, expectedSubhandlers);
}

TEST_F(UTEST_SignalsHandler, the_destructor_uninstalls_every_subhandler)
{
  hook_the_subhandlers(true, Exactly(1));

  EXPECT_TRUE(handler->install(appCtx));

  handler.reset();

  EXPECT_EQ(createdSubhandlers, expectedSubhandlers);
}

TEST_F(UTEST_SignalsHandler, the_repeated_install_releases_the_previous_ones)
{
  hook_the_subhandlers(true, Exactly(1));

  EXPECT_TRUE(handler->install(appCtx));

  // The second install call is expected to uninstall the subhandlers of the
  // first one and to create a brand new set of them.
  hook_the_subhandlers(true, AnyNumber());

  EXPECT_TRUE(handler->install(appCtx));

  EXPECT_EQ(createdSubhandlers, expectedSubhandlers * 2);
}
