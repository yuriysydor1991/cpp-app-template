#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MAIN_WINDOW_COMPONENT_LOADER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MAIN_WINDOW_COMPONENT_LOADER_CLASS_H

#include <memory>

#include "src/gtkmm3/gtkmm_includes.h"

namespace Gtkmm3i::main_window
{

/**
 * @brief The root GTKmm3 window widgets loader class.
 */
class Loader
{
 public:
  using LoaderPtr = std::shared_ptr<Loader>;

  virtual ~Loader() = default;
  Loader() = default;

  static LoaderPtr create();

  virtual bool init();

  virtual Gtk::Window* window();
  virtual Gtk::Image* central_image();

 private:
  bool prepare_widgets();
  static bool load_css();
  bool prepare_random_logo();
  void update_window_title();

  template <class WidgetType>
  WidgetType* get_widget(const std::string& id);

  Glib::RefPtr<Gtk::Builder> builder;
};

using LoaderPtr = Loader::LoaderPtr;

}  // namespace Gtkmm3i::main_window

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MAIN_WINDOW_COMPONENT_LOADER_CLASS_H
