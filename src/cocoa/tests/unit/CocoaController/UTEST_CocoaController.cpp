#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/cocoa/CocoaController.h"
#include "src/cocoa/CocoaLauncher.h"

using namespace cocoa;
using namespace app;
using namespace testing;

// Link-time seam: the orchestration is exercised through the overridden
// launch(), so the real AppKit backed run_cocoa_application() is never needed.
namespace cocoa
{
int run_cocoa_application(int& /*argc*/, char**& /*argv*/,
                          const std::function<bool()>& /*stop_requested*/)
{
  return 0;
}
}  // namespace cocoa

namespace
{

/// @brief Test double that records the launch() invocation instead of starting
/// a real Cocoa application.
class TestController : public CocoaController
{
 public:
  int launch_calls{0};
  int seen_argc{-1};
  int launch_return{0};

 protected:
  int launch(int& argc, char**& /*argv*/) override
  {
    ++launch_calls;
    seen_argc = argc;
    return launch_return;
  }
};

}  // namespace

class UTEST_CocoaController : public Test
{
 public:
  int argc{3};
  char** argv{nullptr};

  TestController controller;

  std::shared_ptr<ApplicationContext> ctx{
      std::make_shared<ApplicationContext>(argc, argv)};
};

TEST_F(UTEST_CocoaController, null_context_is_rejected_without_launching)
{
  EXPECT_NE(controller.run(nullptr), 0);
  EXPECT_EQ(controller.launch_calls, 0);
}

TEST_F(UTEST_CocoaController, valid_context_launches_and_returns_success)
{
  controller.launch_return = 0;

  EXPECT_EQ(controller.run(ctx), 0);
  EXPECT_EQ(controller.launch_calls, 1);
  EXPECT_EQ(controller.seen_argc, 3);
}

TEST_F(UTEST_CocoaController, launch_status_is_propagated)
{
  controller.launch_return = 7;

  EXPECT_EQ(controller.run(ctx), 7);
  EXPECT_EQ(controller.launch_calls, 1);
}
