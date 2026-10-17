#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <functional>
#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"
#include "src/cocoa/CocoaController.h"
#include "src/cocoa/CocoaLauncher.h"
#include "src/cocoa/helpers/WindowConfig.h"

using namespace cocoa;
using namespace app;
using namespace testing;

namespace
{
// Records what the (simulated) Cocoa application does when the real
// CocoaController launches it. This keeps the real run() -> launch() ->
// run_cocoa_application() seam intact while building a real WindowConfig the
// way the AppKit delegate would, so the whole Cocoa free part of the component
// is exercised together without AppKit and without a GUI.
int g_seen_argc = -1;
std::string g_built_title;
std::function<bool()> g_stop_requested;
}  // namespace

namespace cocoa
{
// the seam signature is the CocoaLauncher.h one
// cppcheck-suppress constParameterReference
int run_cocoa_application(int& argc, char**& /*argv*/,
                          const std::function<bool()>& stop_requested)
{
  g_seen_argc = argc;
  g_stop_requested = stop_requested;

  const helpers::WindowConfig config{"ComponentApp", "9.9.9"};
  g_built_title = config.title();

  return 0;
}
}  // namespace cocoa

class CTEST_Cocoa : public Test
{
 public:
  void SetUp() override
  {
    g_seen_argc = -1;
    g_built_title.clear();
    g_stop_requested = nullptr;
  }

  int argc{4};
  char** argv{nullptr};

  CocoaController controller;

  std::shared_ptr<ApplicationContext> ctx{
      std::make_shared<ApplicationContext>(argc, argv)};
};

TEST_F(CTEST_Cocoa, run_launches_app_and_forwards_arguments)
{
  EXPECT_EQ(controller.run(ctx), 0);

  EXPECT_EQ(g_seen_argc, 4);
  EXPECT_EQ(g_built_title, "ComponentApp 9.9.9");
}

TEST_F(CTEST_Cocoa, run_forwards_the_current_argument_count)
{
  argc = 1;  // ctx->get_argc() is a reference to this fixture member

  EXPECT_EQ(controller.run(ctx), 0);

  EXPECT_EQ(g_seen_argc, 1);
  EXPECT_EQ(g_built_title, "ComponentApp 9.9.9");
}

TEST_F(CTEST_Cocoa, run_hands_the_context_stop_flag_to_the_cocoa_application)
{
  EXPECT_EQ(controller.run(ctx), 0);

  ASSERT_TRUE(g_stop_requested);
  EXPECT_FALSE(g_stop_requested());

  ctx->set_stop(true);

  EXPECT_TRUE(g_stop_requested());
}
