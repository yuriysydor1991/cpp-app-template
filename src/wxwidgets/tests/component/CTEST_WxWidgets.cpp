#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"
#include "src/wxwidgets/WxLauncher.h"
#include "src/wxwidgets/WxWidgetsIniter.h"
#include "src/wxwidgets/helpers/WindowConfig.h"

using namespace wxwi;
using namespace app;
using namespace testing;

namespace
{
// Records what the (simulated) wxWidgets application does when the real
// WxWidgetsIniter launches it. This keeps the real run() -> launch() ->
// run_wx_application() seam intact while building a real WindowConfig the way
// WxApp::OnInit() would, so the whole wxWidgets free part of the component is
// exercised together without launching a GUI.
int g_seen_argc = -1;
std::string g_built_title;
}  // namespace

namespace wxwi
{
int run_wx_application(int& argc, char**& /*argv*/)
{
  g_seen_argc = argc;

  const helpers::WindowConfig config{"ComponentApp", "9.9.9"};
  g_built_title = config.title();

  return 0;
}
}  // namespace wxwi

class CTEST_WxWidgets : public Test
{
 public:
  void SetUp() override
  {
    g_seen_argc = -1;
    g_built_title.clear();
  }

  int argc{4};
  char** argv{nullptr};

  WxWidgetsIniter initer;

  std::shared_ptr<ApplicationContext> ctx{
      std::make_shared<ApplicationContext>(argc, argv)};
};

TEST_F(CTEST_WxWidgets, run_launches_app_and_forwards_arguments)
{
  EXPECT_EQ(initer.run(ctx), 0);

  EXPECT_EQ(g_seen_argc, 4);
  EXPECT_EQ(g_built_title, "ComponentApp 9.9.9");
}

TEST_F(CTEST_WxWidgets, run_forwards_the_current_argument_count)
{
  argc = 1;  // ctx->argc is a reference to this fixture member

  EXPECT_EQ(initer.run(ctx), 0);

  EXPECT_EQ(g_seen_argc, 1);
  EXPECT_EQ(g_built_title, "ComponentApp 9.9.9");
}
