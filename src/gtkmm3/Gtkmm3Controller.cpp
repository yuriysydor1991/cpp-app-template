#include "src/gtkmm3/Gtkmm3Controller.h"

#include <algorithm>
#include <cassert>

#include "project-global-decls.h"
#include "src/app/applications/IApplication.h"
#include "src/gtkmm3/gtkmm_includes.h"
#include "src/gtkmm3/log/GtkLogBridge.h"
#include "src/gtkmm3/main-window/Loader.h"
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
    LOGE("Invalid application context provided");
    return app::IApplication::INVALID;
  }

  actx = nactx;

  LOGD("Trying to create the GTKmm3 app instance");

  // The command line belongs to the CommandLineParser alone, so the toolkit
  // gets the program name only and never rejects the application parameters.
  int toolkitArgc = std::min(actx->get_argc(), 1);
  char** toolkitArgv = actx->get_argv();

  auto app = Gtk::Application::create(toolkitArgc, toolkitArgv,
                                      project_decls::PROJECT_FLATPAK_URL);

  if (!init_main_window()) {
    LOGE("Fail to init subsystems");
    return app::IApplication::INVALID;
  }

  LOGD("Starting the GTKmm event loop");

  return app->run(*loader->window());
}

bool Gtkmm3Controller::create_main_window_loader()
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

bool Gtkmm3Controller::prepare_main_window()
{
  assert(loader != nullptr);

  if (loader == nullptr) {
    LOGE("No loader available");
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

bool Gtkmm3Controller::create_events_handler()
{
  assert(loader != nullptr);

  if (loader == nullptr) {
    LOGE("Missing required main window loader instance");
    return false;
  }

  handler = main_window::EventsHandler::create();

  assert(handler != nullptr);

  if (handler == nullptr) {
    LOGE("Obtained invalid events handler instance");
    return false;
  }

  if (!handler->init(loader)) {
    LOGE("Fail to init the event handler instance");
    return false;
  }

  return true;
}

bool Gtkmm3Controller::init_main_window()
{
  LOGD("Trying to initialize main window objects");

  if (!create_main_window_loader()) {
    LOGE("Fail to create the loader");
    return false;
  }

  if (!prepare_main_window()) {
    LOGE("Fail to prepare main window");
    return false;
  }

  if (!create_events_handler()) {
    LOGE("Fail to create the events handler instance");
    return false;
  }

  return true;
}

}  // namespace Gtkmm3i
