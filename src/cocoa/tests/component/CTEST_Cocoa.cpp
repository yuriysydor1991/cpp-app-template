#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"
#include "src/cocoa/CocoaIniter.h"
#include "src/cocoa/CocoaLauncher.h"
#include "src/cocoa/helpers/WindowConfig.h"

using namespace cocoa;
using namespace app;
using namespace testing;

namespace
{
// Records what the (simulated) Cocoa application does when the real CocoaIniter
// launches it. This keeps the real run() -> launch() -> run_cocoa_application()
// seam intact while building a real WindowConfig the way the AppKit delegate
// would, so the whole Cocoa free part of the component is exercised together
// without AppKit and without a GUI.
int g_seen_argc = -1;
std::string g_built_title;
}  // namespace

namespace cocoa
{
int run_cocoa_application(int& argc, char**& /*argv*/)
{
  g_seen_argc = argc;

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
  }

  int argc{4};
  char** argv{nullptr};

  CocoaIniter initer;

  std::shared_ptr<ApplicationContext> ctx{
      std::make_shared<ApplicationContext>(argc, argv)};
};

TEST_F(CTEST_Cocoa, run_launches_app_and_forwards_arguments)
{
  EXPECT_EQ(initer.run(ctx), 0);

  EXPECT_EQ(g_seen_argc, 4);
  EXPECT_EQ(g_built_title, "ComponentApp 9.9.9");
}

TEST_F(CTEST_Cocoa, run_forwards_the_current_argument_count)
{
  argc = 1;  // ctx->argc is a reference to this fixture member

  EXPECT_EQ(initer.run(ctx), 0);

  EXPECT_EQ(g_seen_argc, 1);
  EXPECT_EQ(g_built_title, "ComponentApp 9.9.9");
}
