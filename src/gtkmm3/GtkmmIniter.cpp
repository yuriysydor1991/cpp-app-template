#include "src/gtkmm3/GtkmmIniter.h"

#include <cassert>

#include "GtkmmWindow_glade.h"
#include "random-logo.h"
#include "src/gtkmm3/gtkmm_includes.h"

namespace templateGtkmm3
{

int GtkmmIniter::run(int& argc, char**& argv)
{
  auto app = Gtk::Application::create(argc, argv,
                                      "ua.org.kytok.template.gtkmm3.glade");

  prepare_widgets();

  assert(window != nullptr);
  assert(image != nullptr);

  if (window == nullptr || image == nullptr) {
    throw std::runtime_error("Unable to find some of the main widgets");
  }

  prepare_random_logo();

  window->show_all_children();

  return app->run(*window);
}

void GtkmmIniter::prepare_widgets()
{
  auto ui_string = get_glade_xml_data();

  builder = Gtk::Builder::create_from_string(ui_string);

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
}

void GtkmmIniter::prepare_random_logo()
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

Glib::ustring GtkmmIniter::get_glade_xml_data()
{
  return Glib::ustring(
      reinterpret_cast<const char*>(resources::gladexml::window_xml_data));
}

}  // namespace templateGtkmm3
