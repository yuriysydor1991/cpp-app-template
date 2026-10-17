#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <utility>

#include "src/app/ApplicationContext.h"
#include "src/wxwidgets/WxLauncher.h"
#include "src/wxwidgets/WxWidgetsController.h"

using namespace wxwi;
using namespace app;
using namespace testing;

namespace
{
// Records what the real WxWidgetsController hands over to the (simulated)
// wxWidgets application, which keeps the real run() -> launch() ->
// run_wx_application() seam intact without launching a GUI.
int g_seen_argc = -1;
std::shared_ptr<ApplicationContext> g_seen_ctx;
}  // namespace

namespace wxwi
{
int run_wx_application(std::shared_ptr<::app::ApplicationContext> ctx,
                       int& argc, char**& /*argv*/)
{
  g_seen_argc = argc;
  g_seen_ctx = std::move(ctx);

  return 0;
}
}  // namespace wxwi

class CTEST_WxWidgets : public Test
{
 public:
  void SetUp() override
  {
    g_seen_argc = -1;
    g_seen_ctx.reset();
  }

  void TearDown() override { g_seen_ctx.reset(); }

  int argc{4};
  char** argv{nullptr};

  WxWidgetsController controller;

  std::shared_ptr<ApplicationContext> ctx{
      std::make_shared<ApplicationContext>(argc, argv)};
};

TEST_F(CTEST_WxWidgets, run_launches_app_and_forwards_arguments)
{
  EXPECT_EQ(controller.run(ctx), 0);

  EXPECT_EQ(g_seen_argc, 4);
}

TEST_F(CTEST_WxWidgets, run_forwards_the_current_argument_count)
{
  argc = 1;  // ctx->get_argc() is a reference to this fixture member

  EXPECT_EQ(controller.run(ctx), 0);

  EXPECT_EQ(g_seen_argc, 1);
}

TEST_F(CTEST_WxWidgets, run_hands_the_context_over_to_the_application)
{
  // The wxWidgets application watches the stop flag of this very context.
  EXPECT_EQ(controller.run(ctx), 0);

  EXPECT_EQ(g_seen_ctx, ctx);
}
