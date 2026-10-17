#include "src/gtkmm3/main-window/Loader.h"

#include <cassert>
#include <memory>
#include <string>

#include "project-global-decls.h"
#include "src/gtkmm3/main-window/DataContext.h"
#include "src/log/log.h"

namespace Gtkmm3i::main_window
{

LoaderPtr Loader::create() { return std::make_shared<Loader>(); }

bool Loader::init()
{
  LOGD("Trying to instantiate a builder from resource: "
       << DataContext::UI_res_path);

  try {
    builder = Gtk::Builder::create_from_resource(DataContext::UI_res_path);
  }
  catch (const Glib::Error& ex) {
    LOGE("Fail to build the UI from the resource: " << ex.what());
    return false;
  }

  // The builder hands a top level window over to the caller, which has to
  // delete it, so the loader owns the window from here on.
  mainWindow.reset(get_widget<Gtk::Window>(DataContext::main_window_id));

  if (mainWindow == nullptr) {
    LOGE("No main window in the UI resource");
    return false;
  }

  LOGD("Trying to prepare widgets");

  return prepare_widgets();
}

bool Loader::prepare_widgets()
{
  if (!prepare_random_logo()) {
    LOGE("Fail to prepare random logo");
    return false;
  }

  update_window_title();

  return true;
}

void Loader::update_window_title()
{
  static const std::string basicTitle =
      project_decls::PROJECT_NAME + " " + project_decls::PROJECT_BUILD_VERSION;

  assert(window() != nullptr);

  window()->set_title(basicTitle);
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

Gtk::Window* Loader::window() { return mainWindow.get(); }

Gtk::Image* Loader::central_image()
{
  assert(builder);

  return get_widget<Gtk::Image>(DataContext::central_image_id);
}

}  // namespace Gtkmm3i::main_window
