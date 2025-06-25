#include "src/gtkmm3/GtkmmIniter.h"

#include <cassert>

#include "project-global-decls.h"
#include "src/gtkmm3/GtkmmWindow.h"
#include "src/gtkmm3/gtkmm_includes.h"

namespace templateGtkmm
{

int GtkmmIniter::run(std::shared_ptr<app::ApplicationContext> nactx)
{
  actx = nactx;

  assert(actx != nullptr);

  auto app = Gtk::Application::create(actx->argc, actx->argv,
                                      project_decls::PROJECT_FLATPAK_URL);

  GtkmmWindow window;

  return app->run(window);
}

}  // namespace templateGtkmm
