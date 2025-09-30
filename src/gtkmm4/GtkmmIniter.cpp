#include "src/gtkmm4/GtkmmIniter.h"

#include <cassert>

#include "project-global-decls.h"
#include "src/app/IApplication.h"
#include "src/gtkmm4/gtkmm4_includes.h"
#include "src/gtkmm4/main-window/GtkmmWindow.h"
#include "src/log/log.h"

namespace Gtkmm4i
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

  auto app = Gtk::Application::create(project_decls::PROJECT_FLATPAK_URL);

  LOGD("Starting the GTK3 app");

  return app->make_window_and_run<main_window::GtkmmWindow>(actx->argc,
                                                            actx->argv);
}

}  // namespace Gtkmm4i
