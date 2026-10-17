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
 * touches one: the strings it shows, the GResource bundle it loads from and
 * the libadwaita linkage itself.
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

  EXPECT_THAT(logo, StartsWith(GTKMM_APP_RESOURCES_PREFIX));
  EXPECT_THAT(logo, EndsWith(".png"));
}

TEST_F(CTEST_AdwaitaWindow, logo_resource_is_compiled_into_the_bundle)
{
  // The logo is loaded by it's GResource path, so the path has to name a file
  // the GResource bundle of the binary really carries.
  gsize size{0};

  EXPECT_TRUE(g_resources_get_info(AdwaitaWindow::logo_res_path,
                                   G_RESOURCE_LOOKUP_FLAGS_NONE, &size, nullptr,
                                   nullptr));
  EXPECT_GT(size, 0U);
}

TEST_F(CTEST_AdwaitaWindow, build_rejects_an_empty_application)
{
  AdwaitaWindow window;

  EXPECT_EQ(window.build(Glib::RefPtr<Gtk::Application>{}), nullptr);
}
