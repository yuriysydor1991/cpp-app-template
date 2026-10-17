#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "src/gtkmm4/components/Map.h"

using namespace testing;
using namespace Gtkmm4i::components;

/**
 * @brief Covers the Leaflet page the map widget shows: it has to be compiled
 * into the GResource bundle of the binary and to load the pinned Leaflet files.
 */
class CTEST_Map : public Test
{
 public:
  /// @brief Returns the bundled map page text or an empty one if it's absent.
  static std::string bundled_page()
  {
    GBytes* const bytes = g_resources_lookup_data(
        Map::map_html_res_path, G_RESOURCE_LOOKUP_FLAGS_NONE, nullptr);

    if (bytes == nullptr) {
      return {};
    }

    gsize size{0};
    const auto* const data =
        static_cast<const char*>(g_bytes_get_data(bytes, &size));

    std::string page{data, size};

    g_bytes_unref(bytes);

    return page;
  }
};

TEST_F(CTEST_Map, map_page_is_compiled_into_the_bundle)
{
  const std::string page = bundled_page();

  EXPECT_FALSE(page.empty());
  EXPECT_THAT(page, HasSubstr("L.map("));
}

TEST_F(CTEST_Map, map_page_pins_the_leaflet_files_with_the_integrity_hashes)
{
  const std::string page = bundled_page();

  EXPECT_THAT(page, HasSubstr("leaflet@1.9.4/dist/leaflet.css"));
  EXPECT_THAT(page, HasSubstr("leaflet@1.9.4/dist/leaflet.js"));
  EXPECT_THAT(page,
              HasSubstr("sha256-p4NxAoJBhIIN+hmNHrzRCf9tD/miZyoHS5obTRR9BMY="));
  EXPECT_THAT(page,
              HasSubstr("sha256-20nQCchB9co0qIjJZRGuk2/Z9VM+kNiyxNV1lvTlZBo="));
}
