#include "src/gtkmm4/Gtkmm4Controller.h"

#include <algorithm>
#include <cassert>

#include "project-global-decls.h"
#include "src/app/applications/IApplication.h"
#include "src/gtkmm4/StopFlagWatcher.h"
#include "src/gtkmm4/adwaita_includes.h"
#include "src/gtkmm4/gtkmm4_includes.h"
#include "src/gtkmm4/log/GtkLogBridge.h"
#include "src/gtkmm4/main-window/AdwaitaWindow.h"
#include "src/log/log.h"

namespace Gtkmm4i
{

int Gtkmm4Controller::run(std::shared_ptr<app::ApplicationContext> nactx)
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

  // The Gtk::Application constructor has already initialized GTK and opened
  // the display, so libadwaita is initialized right here, before any of its
  // widgets is created.
  adw_init();

  bool windowBuilt{true};

  // The handler refers to the application instead of holding a reference to
  // it, so the application does not keep itself alive through its own signal.
  app->signal_activate().connect([&app, &windowBuilt]() {
    auto window = create_main_window();

    assert(window != nullptr);

    if (window == nullptr || window->build(app) == nullptr) {
      LOGE("Fail to create the main application window");
      windowBuilt = false;
      app->quit();
    }
  });

  const StopFlagWatcher stopWatcher{actx, *app};

  LOGD("Starting the GTK4 app with the libadwaita widgets");

  // The command line belongs to the CommandLineParser alone, so the toolkit
  // gets the program name only and never rejects the application parameters.
  const int status = app->run(std::min(actx->get_argc(), 1), actx->get_argv());

  return windowBuilt ? status : app::IApplication::INVALID;
}

main_window::AdwaitaWindowPtr Gtkmm4Controller::create_main_window()
{
  return std::make_shared<main_window::AdwaitaWindow>();
}

}  // namespace Gtkmm4i
