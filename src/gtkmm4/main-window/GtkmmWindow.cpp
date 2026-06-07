#include "src/gtkmm4/main-window/GtkmmWindow.h"

#include <string>

#include "project-global-decls.h"
#include "src/log/log.h"

namespace Gtkmm4i::main_window
{

GtkmmWindow::GtkmmWindow()
{
  if (!init()) {
    LOGE("Fail to init");
  }
}

bool GtkmmWindow::init()
{
  prepare_window();

  return true;
}

void GtkmmWindow::prepare_window()
{
  set_title(get_default_title());

  set_default_size(W_DEFAULT_WIDTH, W_DEFAULT_HEIGHT);

  prepare_css();
}

void GtkmmWindow::prepare_css()
{
  auto css_provider = Gtk::CssProvider::create();

  try {
    css_provider->load_from_resource(main_css_res_path);
  }
  catch (const Glib::Error& ex) {
    LOGE("Failed to load CSS: " << ex.what());
    return;
  }

  auto display = Gdk::Display::get_default();
  Gtk::StyleProvider::add_provider_for_display(
      display, css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

const std::string& GtkmmWindow::get_default_title()
{
  static const std::string default_title =
      std::string{project_decls::PROJECT_NAME} + " " +
      project_decls::PROJECT_BUILD_VERSION;

  return default_title;
}

GtkmmWindowPtr GtkmmWindow::create() { return std::make_shared<GtkmmWindow>(); }

}  // namespace Gtkmm4i::main_window
