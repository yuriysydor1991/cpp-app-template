#include "src/gtkmm4/components/Map.h"

#include <webkit/webkit.h>

#include <string>

#include "src/log/log.h"

namespace Gtkmm4i::components
{

namespace
{
// Leaflet and the OpenStreetMap tiles are fetched over the network, so the
// embedded page is served from a remote base URI rather than a local one.
constexpr const char* const map_base_uri = "https://www.openstreetmap.org/";
}  // namespace

Map::Map()
{
  set_orientation(Gtk::Orientation::VERTICAL);

  auto* const web_view = webkit_web_view_new();

  auto* const wrapped = Glib::wrap(web_view);
  wrapped->set_expand(true);
  append(*wrapped);

  show_leaflet(web_view);
}

void Map::show_leaflet(GtkWidget* web_view)
{
  try {
    const auto bytes = Gio::Resource::lookup_data_global(map_html_res_path);

    gsize size = 0;
    const auto* const data = static_cast<const char*>(bytes->get_data(size));

    webkit_web_view_load_html(WEBKIT_WEB_VIEW(web_view),
                              std::string(data, size).c_str(), map_base_uri);
  }
  catch (const Glib::Error& ex) {
    LOGE("Failed to load the Leaflet map page: " << ex.what());
  }
}

}  // namespace Gtkmm4i::components
