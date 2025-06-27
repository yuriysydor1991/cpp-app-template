#include "src/gtkmm3/GtkmmIniter.h"

#include <cassert>

#include "project-global-decls.h"
#include "src/gtkmm3/gtkmm_includes.h"

namespace Gtkmm3i
{

int GtkmmIniter::run(std::shared_ptr<app::ApplicationContext> nactx)
{
  actx = nactx;

  assert(actx != nullptr);

  auto app = Gtk::Application::create(actx->argc, actx->argv,
                                      project_decls::PROJECT_FLATPAK_URL);

  prepare_widgets();

  assert(window != nullptr);
  assert(image != nullptr);

  if (window == nullptr || image == nullptr) {
    throw std::runtime_error("Unable to find some of the main widgets");
  }

  window->show_all_children();

  return app->run(*window);
}

void GtkmmIniter::prepare_widgets()
{
  builder = Gtk::Builder::create_from_resource(UI_res_path);

  if (!builder) {
    throw std::runtime_error("Failed to create the builder");
  }

  builder->get_widget("main_window", window);

  if (window == nullptr) {
    throw std::runtime_error("Failed to get the main window");
  }

  builder->get_widget("random_image", image);

  if (image == nullptr) {
    throw std::runtime_error("Failed to get an image");
  }

  load_css();
  prepare_random_logo();
}

inline void GtkmmIniter::load_css()
{
  auto css = Gtk::CssProvider::create();

  assert(css);

  css->load_from_resource(main_css_res_path);

  auto screen = Gdk::Display::get_default()->get_default_screen();
  Gtk::StyleContext::add_provider_for_screen(
      screen, css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

inline void GtkmmIniter::prepare_random_logo()
{
  assert(image != nullptr);

  if (image == nullptr) {
    return;
  }

  image->set_from_resource(logo_res_path);
}

}  // namespace Gtkmm3i
