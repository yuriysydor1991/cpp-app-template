#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4WINDOW_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4WINDOW_CLASS_H

#include <memory>
#include <string>

#include "src/gtkmm4/components/Map.h"
#include "src/gtkmm4/gtkmm4_includes.h"

namespace Gtkmm4i::main_window
{

/**
 * @brief The root GTKmm window class that shows the Leaflet map.
 */
class GtkmmWindow : public Gtk::Window
{
 public:
  using GtkmmWindowPtr = std::shared_ptr<GtkmmWindow>;

  virtual ~GtkmmWindow() = default;
  GtkmmWindow();

  bool init();

  static GtkmmWindowPtr create();

 protected:
  const std::string& get_default_title();

 private:
  void prepare_window();

  components::Map map;
};

using GtkmmWindowPtr = GtkmmWindow::GtkmmWindowPtr;

}  // namespace Gtkmm4i::main_window

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4WINDOW_CLASS_H
