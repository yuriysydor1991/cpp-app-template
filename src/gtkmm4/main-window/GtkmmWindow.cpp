#include "src/gtkmm4/main-window/GtkmmWindow.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include "project-global-decls.h"
#include "src/log/log.h"

namespace Gtkmm4i::main_window
{

GtkmmWindow::GtkmmWindow()
    : box{},
      headerText{"Main GTKmm application"},
      explanationText{
          "Replace the default window implementation in GtkmmWindow class"}
{
  if (!init()) {
    LOGE("Fail to init");
  }
}

bool GtkmmWindow::init()
{
  prepare_widgets();

  pack_widgets();

  return true;
}

void GtkmmWindow::pack_widgets()
{
  box.set_orientation(Gtk::Orientation::VERTICAL);
  box.set_homogeneous(false);

  box.append(headerText);
  box.append(explanationText);

  image.set_vexpand(true);
  image.set_hexpand(true);

  box.append(image);

  set_child(box);
}

void GtkmmWindow::prepare_widgets()
{
  set_title(get_default_title());

  set_size_request(400, 300);
  set_default_size(500, 400);

  prepare_header_label();
  prepare_random_logo();
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
  Gtk::StyleContext::add_provider_for_display(
      display, css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

void GtkmmWindow::prepare_header_label()
{
  headerText.get_style_context()->add_class(header_label_class);
}

void GtkmmWindow::prepare_random_logo()
{
  image.set_from_resource(logo_res_path);
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
