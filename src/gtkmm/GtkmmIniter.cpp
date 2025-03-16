#include "src/gtkmm/GtkmmIniter.h"

#include "src/gtkmm/GtkmmWindow.h"
#include "src/gtkmm/gtkmm_includes.h"
#include "project-global-decls.h"

namespace templateGtkmm
{

int GtkmmIniter::run(int& argc, char**& argv)
{
  auto app =
      Gtk::Application::create(argc, argv, "ua.org.kytok.template.gtkmm3");

  GtkmmWindow window;

  return app->run(window);
}

}  // namespace templateGtkmm
