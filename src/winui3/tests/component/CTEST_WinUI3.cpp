#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"
#include "src/winui3/WinUI3Initer.h"
#include "src/winui3/WinUI3Launcher.h"
#include "src/winui3/helpers/WindowConfig.h"

using namespace winui3;
using namespace app;
using namespace testing;

namespace
{
// Records what the (simulated) WinUI 3 application does when the real
// WinUI3Initer launches it. This keeps the real run() -> launch() ->
// run_winui_application() seam intact while building a real WindowConfig the way
// WinUI3App::OnLaunched() would, so the whole WinUI free part of the component
// is exercised together without the Windows App SDK and without a GUI.
int g_seen_argc = -1;
std::string g_built_title;
}  // namespace

namespace winui3
{
int run_winui_application(int& argc, char**& /*argv*/)
{
  g_seen_argc = argc;

  const helpers::WindowConfig config{"ComponentApp", "9.9.9"};
  g_built_title = config.title();

  return 0;
}
}  // namespace winui3

class CTEST_WinUI3 : public Test
{
 public:
  void SetUp() override
  {
    g_seen_argc = -1;
    g_built_title.clear();
  }

  int argc{4};
  char** argv{nullptr};

  WinUI3Initer initer;

  std::shared_ptr<ApplicationContext> ctx{
      std::make_shared<ApplicationContext>(argc, argv)};
};

TEST_F(CTEST_WinUI3, run_launches_app_and_forwards_arguments)
{
  EXPECT_EQ(initer.run(ctx), 0);

  EXPECT_EQ(g_seen_argc, 4);
  EXPECT_EQ(g_built_title, "ComponentApp 9.9.9");
}

TEST_F(CTEST_WinUI3, run_forwards_the_current_argument_count)
{
  argc = 1;  // ctx->argc is a reference to this fixture member

  EXPECT_EQ(initer.run(ctx), 0);

  EXPECT_EQ(g_seen_argc, 1);
  EXPECT_EQ(g_built_title, "ComponentApp 9.9.9");
}
