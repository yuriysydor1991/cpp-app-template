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

  if (!create_main_window_loader()) {
    LOGE("Fail to create the loader");
    return false;
  }

  if (!prepare_main_window()) {
    LOGE("Fail to prepare main window");
    return app::IApplication::INVALID;
  }

  LOGD("Starting the GTKmm event loop");

  return app->run(*loader->window());
}

bool GtkmmIniter::create_main_window_loader()
{
  LOGD("Creating the main window loader instance");

  loader = main_window::Loader::create();

  assert(loader != nullptr);

  if (!loader->init()) {
    LOGE("Failure while init loader");
    return false;
  }

  return true;
}

bool GtkmmIniter::prepare_main_window()
{
  assert(loader != nullptr);

  if (loader == nullptr) {
    LOGE("No loader avaialble");
    return false;
  }

  auto* window = loader->window();

  assert(window != nullptr);

  if (window == nullptr) {
    LOGE("Obtained invalid main window pointer");
    return false;
  }

  window->show_all_children();

  return true;
}

}  // namespace Gtkmm3i
