#include "src/gtkmm3/GtkmmIniter.h"

#include <cassert>

#include "project-global-decls.h"
#include "src/app/IApplication.h"
#include "src/gtkmm3/gtkmm_includes.h"
#include "src/gtkmm3/main-window/Loader.h"
#include "src/log/log.h"

namespace Gtkmm3i
{

int GtkmmIniter::run(std::shared_ptr<app::ApplicationContext> nactx)
{
  assert(nactx != nullptr);

  if (nactx == nullptr) {
    LOGE("Invalid application context provided");
    return app::IApplication::INVALID;
  }

  actx = nactx;

  LOGD("Trying to create the GTKmm3 app instance");

  auto app = Gtk::Application::create(actx->argc, actx->argv,
                                      project_decls::PROJECT_FLATPAK_URL);

  LOGD("Creating the main window loader instance");

  auto loader = main_window::Loader::create();

  assert(loader != nullptr);

  if (!loader->init()) {
    LOGE("Failure while init loader");
    return app::IApplication::INVALID;
  }

  auto* window = loader->window();

  assert(window != nullptr);

  if (window == nullptr) {
    LOGE("Obtained invalid main window pointer");
    return app::IApplication::INVALID;
  }

  window->show_all_children();

  LOGD("Starting the GTKmm event loop");

  return app->run(*window);
}

}  // namespace Gtkmm3i
