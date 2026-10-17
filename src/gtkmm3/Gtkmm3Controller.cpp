#include "src/gtkmm3/Gtkmm3Controller.h"

#include <algorithm>
#include <cassert>

#include "project-global-decls.h"
#include "src/app/applications/IApplication.h"
#include "src/gtkmm3/gtkmm_includes.h"
#include "src/gtkmm3/log/GtkLogBridge.h"
#include "src/gtkmm3/main-window/GtkmmWindow.h"
#include "src/log/log.h"

namespace Gtkmm3i
{

int Gtkmm3Controller::run(std::shared_ptr<app::ApplicationContext> nactx)
{
  // Every message the toolkit reports lands in the application log from here
  // on. It is taken over before anything of the toolkit is touched, so the
  // complaints of it's own start up are caught as well.
  gtklog::GtkLogBridge::install();

  assert(nactx != nullptr);

  if (nactx == nullptr) {
    LOGE("Invalid context pointer provided");
    return app::IApplication::INVALID;
  }

  actx = nactx;

  LOGD("Trying to create the GTK3 app instance");

  // The command line belongs to the CommandLineParser alone, so the toolkit
  // gets the program name only and never rejects the application parameters.
  int toolkitArgc = std::min(actx->get_argc(), 1);
  char** toolkitArgv = actx->get_argv();

  auto app = Gtk::Application::create(toolkitArgc, toolkitArgv,
                                      project_decls::PROJECT_FLATPAK_URL);

  LOGD("Trying to create the GtkmmWindow instance");

  auto window = main_window::GtkmmWindow::create();

  assert(window != nullptr);

  if (!window->init()) {
    LOGE("Fail to init the main window");
    return false;
  }

  LOGD("Starting the GTK3 app");

  return app->run(*window);
}

}  // namespace Gtkmm3i
