#include "src/gtkmm4/GtkmmIniter.h"

#include <cassert>

#include "project-global-decls.h"
#include "src/app/applications/IApplication.h"
#include "src/gtkmm4/adwaita_includes.h"
#include "src/gtkmm4/gtkmm4_includes.h"
#include "src/gtkmm4/main-window/AdwaitaWindow.h"
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

  LOGD("Trying to create the GTK4 app instance");

  auto app = Gtk::Application::create(project_decls::PROJECT_REVERSE_URL);

  // libadwaita has to be initialized before any of its widgets is created. It
  // is done in the activate handler and not before the run call, because
  // adw_init needs the GTK display, which the application opens for itself.
  // Calling it twice is harmless - the second call is a documented no-op.
  app->signal_activate().connect([app]() {
    adw_init();

    auto window = create_main_window();

    assert(window != nullptr);

    if (window == nullptr) {
      LOGE("Fail to create the main application window");
      return;
    }

    window->build(app);
  });

  LOGD("Starting the GTK4 app with the libadwaita widgets");

  return app->run(actx->get_argc(), actx->get_argv());
}

main_window::AdwaitaWindowPtr GtkmmIniter::create_main_window()
{
  return std::make_shared<main_window::AdwaitaWindow>();
}

}  // namespace Gtkmm4i
