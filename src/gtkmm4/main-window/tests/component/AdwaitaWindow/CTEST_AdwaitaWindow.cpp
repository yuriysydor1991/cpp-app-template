#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "project-global-decls.h"
#include "src/gtkmm4/main-window/AdwaitaWindow.h"

using namespace testing;
using namespace Gtkmm4i::main_window;

/**
 * @brief The window widget tree can not be built without an opened GTK
 * display, so these tests cover everything the window decides before it
 * touches one: the strings it shows, the GResource paths it loads from, the
 * geometry it requests and the libadwaita linkage itself.
 */
class CTEST_AdwaitaWindow : public Test
{
};

TEST_F(CTEST_AdwaitaWindow, libadwaita_is_linked_and_usable)
{
  // Proves the enabler found libadwaita and the binary really links against
  // it. It queries the runtime version, so no display is involved.
  EXPECT_GE(adw_get_major_version(), 1U);
}

TEST_F(CTEST_AdwaitaWindow, default_title_carries_the_project_identity)
{
  const std::string& title = AdwaitaWindow::get_default_title();

  EXPECT_FALSE(title.empty());
  EXPECT_THAT(title, HasSubstr(project_decls::PROJECT_NAME));
  EXPECT_THAT(title, HasSubstr(project_decls::PROJECT_BUILD_VERSION));
}

TEST_F(CTEST_AdwaitaWindow, default_title_is_a_stable_reference)
{
  // The window hands the title over to the C API as a raw pointer, so the
  // referenced string has to outlive the call.
  const std::string& first = AdwaitaWindow::get_default_title();
  const std::string& second = AdwaitaWindow::get_default_title();

  EXPECT_EQ(&first, &second);
}

TEST_F(CTEST_AdwaitaWindow, default_description_is_present)
{
  const std::string& description = AdwaitaWindow::get_default_description();

  EXPECT_FALSE(description.empty());
  EXPECT_THAT(description, HasSubstr("AdwaitaWindow"));
}

TEST_F(CTEST_AdwaitaWindow, resource_paths_live_under_the_resources_prefix)
{
  const std::string logo{AdwaitaWindow::logo_res_path};
  const std::string css{AdwaitaWindow::main_css_res_path};

  EXPECT_THAT(logo, StartsWith(GTKMM_APP_RESOURCES_PREFIX));
  EXPECT_THAT(css, StartsWith(GTKMM_APP_RESOURCES_PREFIX));
  EXPECT_THAT(logo, EndsWith(".png"));
  EXPECT_THAT(css, EndsWith(".css"));
}

TEST_F(CTEST_AdwaitaWindow, the_heading_is_styled_as_the_libadwaita_h1)
{
  // The heading is enlarged by the libadwaita typography style class and not
  // by a custom CSS rule, so the window keeps following the light and the dark
  // libadwaita palettes.
  EXPECT_STREQ(AdwaitaWindow::title_style_class, "title-1");
}

TEST_F(CTEST_AdwaitaWindow, the_description_is_the_smaller_text)
{
  EXPECT_STREQ(AdwaitaWindow::description_style_class, "body");
  EXPECT_STREQ(AdwaitaWindow::dim_style_class, "dim-label");
  EXPECT_STRNE(AdwaitaWindow::description_style_class,
               AdwaitaWindow::title_style_class);
}

TEST_F(CTEST_AdwaitaWindow, the_logo_grows_over_the_free_space_undeformed)
{
  // The GTK_CONTENT_FIT_SCALE_DOWN would keep the logo at its own pixel size
  // instead of letting it grow over the height the labels leave free, and the
  // GTK_CONTENT_FIT_FILL would grow it into a deformed one.
  EXPECT_EQ(AdwaitaWindow::logo_content_fit, GTK_CONTENT_FIT_CONTAIN);
  EXPECT_NE(AdwaitaWindow::logo_content_fit, GTK_CONTENT_FIT_SCALE_DOWN);
  EXPECT_NE(AdwaitaWindow::logo_content_fit, GTK_CONTENT_FIT_FILL);
}

TEST_F(CTEST_AdwaitaWindow, the_content_paddings_fit_the_minimal_window)
{
  EXPECT_GE(AdwaitaWindow::content_spacing, 0);
  EXPECT_GE(AdwaitaWindow::content_margin, 0);
  EXPECT_LT(AdwaitaWindow::content_margin, AdwaitaWindow::min_width);
  EXPECT_LT(AdwaitaWindow::content_margin, AdwaitaWindow::min_height);
}

TEST_F(CTEST_AdwaitaWindow, default_geometry_fits_the_minimal_one)
{
  // libadwaita targets the adaptive layouts, so the window must be able to
  // shrink down to the mobile width without breaking its own default size.
  EXPECT_GT(AdwaitaWindow::default_width, 0);
  EXPECT_GT(AdwaitaWindow::default_height, 0);
  EXPECT_GT(AdwaitaWindow::min_width, 0);
  EXPECT_GT(AdwaitaWindow::min_height, 0);
  EXPECT_LE(AdwaitaWindow::min_width, AdwaitaWindow::default_width);
  EXPECT_LE(AdwaitaWindow::min_height, AdwaitaWindow::default_height);
}

TEST_F(CTEST_AdwaitaWindow, build_rejects_an_empty_application)
{
  AdwaitaWindow window;

  EXPECT_EQ(window.build(Glib::RefPtr<Gtk::Application>{}), nullptr);
}
