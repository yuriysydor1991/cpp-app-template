#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/wxwidgets/WxLauncher.h"
#include "src/wxwidgets/WxWidgetsIniter.h"

using namespace wxwi;
using namespace app;
using namespace testing;

// Link-time seam: the orchestration is exercised through the overridden
// launch(), so the real wxWidgets backed run_wx_application() is never needed.
namespace wxwi
{
int run_wx_application(int& /*argc*/, char** & /*argv*/) { return 0; }
}  // namespace wxwi

namespace
{

/// @brief Test double that records the launch() invocation instead of starting
/// a real wxWidgets event loop.
class TestIniter : public WxWidgetsIniter
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

class UTEST_WxWidgetsIniter : public Test
{
 public:
  int argc{3};
  char** argv{nullptr};

  TestIniter initer;

  std::shared_ptr<ApplicationContext> ctx{
      std::make_shared<ApplicationContext>(argc, argv)};
};

TEST_F(UTEST_WxWidgetsIniter, null_context_is_rejected_without_launching)
{
  EXPECT_NE(initer.run(nullptr), 0);
  EXPECT_EQ(initer.launch_calls, 0);
}

TEST_F(UTEST_WxWidgetsIniter, valid_context_launches_and_returns_success)
{
  initer.launch_return = 0;

  EXPECT_EQ(initer.run(ctx), 0);
  EXPECT_EQ(initer.launch_calls, 1);
  EXPECT_EQ(initer.seen_argc, 3);
}

TEST_F(UTEST_WxWidgetsIniter, launch_status_is_propagated)
{
  initer.launch_return = 7;

  EXPECT_EQ(initer.run(ctx), 7);
  EXPECT_EQ(initer.launch_calls, 1);
}
