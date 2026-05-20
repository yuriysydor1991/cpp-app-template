#include "src/wxwidgets/app/WxApp.h"

#include "project-global-decls.h"
#include "src/wxwidgets/WxLauncher.h"
#include "src/wxwidgets/helpers/WindowConfig.h"
#include "src/wxwidgets/main-window/WxMainFrame.h"

// Register the application object without letting wxWidgets define main(): the
// template keeps its own main()/ApplicationFactory entry point and starts
// wxWidgets explicitly through wxEntry() in run_wx_application() below.
using TemplateWxApp = wxwi::app::WxApp;
wxIMPLEMENT_APP_NO_MAIN(TemplateWxApp);

namespace wxwi
{

int run_wx_application(int& argc, char**& argv)
{
  return wxEntry(argc, argv);
}

}  // namespace wxwi

namespace wxwi::app
{

bool WxApp::OnInit()
{
  const helpers::WindowConfig config{project_decls::PROJECT_NAME,
                                     project_decls::PROJECT_BUILD_VERSION};

  auto* frame = new main_window::WxMainFrame(config);
  frame->Show(true);

  return true;
}

}  // namespace wxwi::app
