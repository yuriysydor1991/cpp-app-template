#include "src/wxwidgets/app/WxApp.h"

#include <cassert>
#include <utility>

#include "project-global-decls.h"
#include "src/wxwidgets/WxLauncher.h"
#include "src/wxwidgets/helpers/WindowConfig.h"
#include "src/wxwidgets/main-window/WxMainFrame.h"

namespace wxwi
{

int run_wx_application(std::shared_ptr<::app::ApplicationContext> ctx,
                       int& argc, char**& argv)
{
  // The application object is created here and not by the wxIMPLEMENT_APP
  // family, so it gets the application context. The template keeps its own
  // main()/ApplicationFactory entry point, and wxEntry() deletes the object on
  // it's cleanup.
  wxApp::SetInstance(new app::WxApp{std::move(ctx)});

  return wxEntry(argc, argv);
}

}  // namespace wxwi

namespace wxwi::app
{

WxApp::WxApp(std::shared_ptr<::app::ApplicationContext> nactx)
    : actx{std::move(nactx)}
{
  assert(actx != nullptr);
}

bool WxApp::OnInit()
{
  const helpers::WindowConfig config{project_decls::PROJECT_NAME,
                                     project_decls::PROJECT_BUILD_VERSION};

  auto* frame = new main_window::WxMainFrame(config);
  frame->Show(true);

  stopWatcher = std::make_unique<StopFlagWatcher>(actx);
  stopWatcher->Start(StopFlagWatcher::poll_period_ms);

  return true;
}

int WxApp::OnExit()
{
  stopWatcher.reset();

  return wxApp::OnExit();
}

}  // namespace wxwi::app
