#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4_MAP_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4_MAP_CLASS_H

#include "src/gtkmm4/gtkmm4_includes.h"

namespace Gtkmm4i::components
{

/**
 * @brief A widget that renders free Leaflet / OpenStreetMap maps
 * inside an embedded WebKitGTK web view.
 */
class Map : public Gtk::Box
{
 public:
  Map();

 private:
  void show_leaflet(GtkWidget* web_view);

  inline static constexpr const char* const map_html_res_path =
      GTKMM_APP_RESOURCES_PREFIX "/resources/html/map.html";
};

}  // namespace Gtkmm4i::components

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4_MAP_CLASS_H
