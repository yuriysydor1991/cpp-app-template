#include "src/gtkmm/GtkmmWindow.h"

#include <cassert>
#include <iostream>

#include "project-global-decls.h"
#include "random-logo.h"
#include "GtkmmWindow_glade.h"

namespace templateGtkmm
{

GtkmmWindow::GtkmmWindow()
{
  set_title(get_default_title());

  set_size_request(400, 300);
  set_default_size(500, 400);

  Glib::ustring ui_string(reinterpret_cast<const char*>(resources::gladexml::window_xml_data));

  builder = Gtk::Builder::create_from_string(ui_string);

  if (!builder) {
    throw std::runtime_error("Failed to create the builder");
  }

  builder->get_widget("main_box", box);

  if (box == nullptr) {
    throw std::runtime_error("Failed to get the main window box");
  }

  builder->get_widget("random_image", image);

  if (image == nullptr) {
    throw std::runtime_error("Failed to get an image");
  }

  prepare_random_logo();

  add(*box);

  show_all_children();
}

void GtkmmWindow::prepare_random_logo()
{
  assert(image != nullptr);

  if (image == nullptr) {
    return;
  }

  // Create Pixbuf from memory
  Glib::RefPtr<Gdk::PixbufLoader> loader = Gdk::PixbufLoader::create();

  loader->write(resources::images::random_logo_data,
                resources::images::random_logo_data_size);
  loader->close();

  image->set(loader->get_pixbuf());
}

const std::string& GtkmmWindow::get_default_title()
{
  static const std::string default_title =
      std::string{project_decls::PROJECT_NAME} + " " +
      project_decls::PROJECT_BUILD_VERSION;

  return default_title;
}

}  // namespace templateGtkmm
