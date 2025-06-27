#include "src/gtkmm3/GtkmmWindow.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include "project-global-decls.h"

namespace Gtkmm3i
{

GtkmmWindow::GtkmmWindow()
    : box{},
      headerText{"Main GTKmm application"},
      explanationText{
          "Replace the default window implementation in GtkmmWindow class"}
{
  set_title(get_default_title());

  set_size_request(400, 300);
  set_default_size(500, 400);

  prepare_widgets();

  box.set_homogeneous(false);

  box.pack_start(headerText, false, false);
  box.pack_start(explanationText, false, false);
  box.pack_start(image, true, true);

  add(box);

  show_all_children();
}

void GtkmmWindow::prepare_widgets()
{
  prepare_header_label();
  prepare_random_logo();
  prepare_css();
}

void GtkmmWindow::prepare_css()
{
  auto css = Gtk::CssProvider::create();

  assert(css);

  css->load_from_resource(main_css_res_path);

  auto screen = Gdk::Display::get_default()->get_default_screen();
  Gtk::StyleContext::add_provider_for_screen(
      screen, css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
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

}  // namespace Gtkmm3i
