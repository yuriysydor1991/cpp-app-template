#include "src/gtkmm3/GtkmmIniter.h"

#include "project-global-decls.h"
#include "src/gtkmm3/GtkmmWindow.h"
#include "src/gtkmm3/gtkmm_includes.h"

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
