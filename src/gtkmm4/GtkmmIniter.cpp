#include "src/gtkmm4/GtkmmIniter.h"

#include <cassert>

#include "project-global-decls.h"
#include "src/app/applications/IApplication.h"
#include "src/gtkmm4/gtkmm4_includes.h"
#include "src/gtkmm4/log/GtkLogBridge.h"
#include "src/gtkmm4/main-window/GtkmmWindow.h"
#include "src/log/log.h"

namespace Gtkmm4i
{

int GtkmmIniter::run(std::shared_ptr<app::ApplicationContext> nactx)
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

  LOGD("Trying to create the GTK4 app instance");

  auto app = Gtk::Application::create(project_decls::PROJECT_REVERSE_URL);

  LOGD("Starting the GTK4 app");

  return app->make_window_and_run<main_window::GtkmmWindow>(actx->get_argc(),
                                                            actx->get_argv());
}

}  // namespace Gtkmm4i
