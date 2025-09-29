#include "src/gtkmm3/GtkmmIniter.h"

#include <cassert>

#include "project-global-decls.h"
#include "src/app/IApplication.h"
#include "src/gtkmm3/gtkmm_includes.h"
#include "src/gtkmm3/main-window/GtkmmWindow.h"
#include "src/log/log.h"

namespace Gtkmm3i
{

int GtkmmIniter::run(std::shared_ptr<app::ApplicationContext> nactx)
{
  assert(nactx != nullptr);

  if (nactx == nullptr) {
    LOGE("Invalid context pointer provided");
    return app::IApplication::INVALID;
  }

  actx = nactx;

  LOGD("Trying to create the GTK3 app instance");

  auto app = Gtk::Application::create(actx->argc, actx->argv,
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
