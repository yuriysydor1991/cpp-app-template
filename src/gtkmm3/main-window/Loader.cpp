#include "src/gtkmm3/main-window/Loader.h"

#include <cassert>
#include <memory>
#include <string>

#include "src/gtkmm3/main-window/DataContext.h"
#include "src/log/log.h"

namespace Gtkmm3i::main_window
{

LoaderPtr Loader::create() { return std::make_shared<Loader>(); }

bool Loader::init()
{
  LOGD("Trying to instantiate a builder from resource: "
       << DataContext::UI_res_path);

  builder = Gtk::Builder::create_from_resource(DataContext::UI_res_path);

  assert(builder);

  if (!builder) {
    LOGE("Invalid builder obtained");
    return false;
  }

  LOGD("Trying to prepare widgets");

  prepare_widgets();

  return true;
}

bool Loader::prepare_widgets()
{
  if (!builder) {
    LOGE("Failed to create the builder");
    return false;
  }

  if (!load_css()) {
    LOGE("Fail to load the CSS");
    return false;
  }

  if (!prepare_random_logo()) {
    LOGE("Fail to prepare random logo");
    return false;
  }

  return true;
}

bool Loader::load_css()
{
  LOGD("Trying to load the CSS");

  auto css = Gtk::CssProvider::create();

  assert(css);

  if (!css) {
    LOGE("Obtained invalid CSS provider pointer");
    return false;
  }

  css->load_from_resource(DataContext::main_css_res_path);

  auto screen = Gdk::Display::get_default()->get_default_screen();
  Gtk::StyleContext::add_provider_for_screen(
      screen, css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  return true;
}

bool Loader::prepare_random_logo()
{
  auto* image = central_image();

  assert(image != nullptr);

  if (image == nullptr) {
    LOGE("Obtained invalid central image pointer");
    return false;
  }

  image->set_from_resource(DataContext::logo_res_path);

  return true;
}

template <class WidgetType>
WidgetType* Loader::get_widget(const std::string& id)
{
  assert(builder);

  if (!builder) {
    LOGE("No builder available");
    return {};
  }

  LOGT("Trying to find widget by id: " << id);

  WidgetType* tptr{nullptr};

  builder->get_widget(id, tptr);

  assert(tptr != nullptr);

  if (tptr == nullptr) {
    LOGE("Failure during retrieving the widget by id: " << id);
    return nullptr;
  }

  return tptr;
}

Gtk::Window* Loader::window()
{
  assert(builder);

  return get_widget<Gtk::Window>(DataContext::main_window_id);
}

Gtk::Image* Loader::central_image()
{
  assert(builder);

  return get_widget<Gtk::Image>(DataContext::central_image_id);
}

}  // namespace Gtkmm3i::main_window
