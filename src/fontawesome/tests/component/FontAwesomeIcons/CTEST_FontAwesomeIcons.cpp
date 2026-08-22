#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <set>
#include <sstream>
#include <string>

#include "fontawesome-decls.h"
#include "src/fontawesome/icons/FontAwesomeIcons.h"
#include "src/fontawesome/resources/FontAwesomeGResourcePath.h"
#include "src/fontawesome/resources/FontAwesomeQtResourcePath.h"
#include "src/fontawesome/styles/FontAwesomeStyles.h"

using namespace fontawesome;
using namespace testing;

/**
 * @brief Component test of the whole icon set against the very Font Awesome
 * checkout the project has been configured with.
 *
 * Nothing is mocked here: the generated icon names index, the generated
 * resource manifests and the SVG files on the disk are checked against each
 * other, so a checkout the enabler failed to gather completely fails the suite
 * instead of quietly shipping a partial icon set.
 */
class CTEST_FontAwesomeIcons : public Test
{
 public:
  CTEST_FontAwesomeIcons()
      : styles{FontAwesomeStyles::create()}, icons{FontAwesomeIcons::create()}
  {
  }

  /// @brief Counts the SVG files the checkout holds for the given style.
  static std::size_t checkoutCountOf(const std::string& styleName)
  {
    const std::filesystem::path styleDir{
        fontawesome_decls::FONTAWESOME_SVGS_DIR + "/" + styleName};

    if (!std::filesystem::is_directory(styleDir)) {
      return 0U;
    }

    std::size_t count = 0;

    for (const auto& entry : std::filesystem::directory_iterator{styleDir}) {
      if (entry.is_regular_file() && entry.path().extension() == ".svg") {
        ++count;
      }
    }

    return count;
  }

  /// @brief Gathers the aliases the given resource manifest keys it's files
  /// by, which is the single naming the manifest and the code agree upon.
  static std::set<std::string> aliasesOf(const std::string& manifestPath)
  {
    static const std::string aliasMark = "alias=\"";

    std::set<std::string> aliases;

    std::ifstream manifest{manifestPath};

    if (!manifest.is_open()) {
      return aliases;
    }

    std::string line;

    while (std::getline(manifest, line)) {
      const auto aliasStart = line.find(aliasMark);

      if (aliasStart == std::string::npos) {
        continue;
      }

      const auto valueStart = aliasStart + aliasMark.size();
      const auto valueEnd = line.find('"', valueStart);

      if (valueEnd == std::string::npos) {
        continue;
      }

      aliases.insert(line.substr(valueStart, valueEnd - valueStart));
    }

    return aliases;
  }

  std::set<std::string> gatheredAliases() const
  {
    std::set<std::string> aliases;

    for (const auto& icon : icons->all()) {
      aliases.insert(icon->alias());
    }

    return aliases;
  }

  IFontAwesomeStylesPtr styles;
  IFontAwesomeIconsPtr icons;
};

TEST_F(CTEST_FontAwesomeIcons, the_checkout_icons_are_available)
{
  ASSERT_NE(icons, nullptr);

  EXPECT_GT(icons->count(), 0U);
  EXPECT_EQ(icons->all().size(), icons->count());
}

TEST_F(CTEST_FontAwesomeIcons, every_gathered_style_is_gathered_completely)
{
  // A project configured with a FONTAWESOME_STYLES subset gathers that subset
  // only, so the styles left out of it are skipped rather than demanded here.
  std::size_t checkedStyles = 0;

  for (const auto& style : styles->all()) {
    ASSERT_NE(style, nullptr);

    const auto gathered = icons->ofStyle(style->name());

    if (gathered.empty()) {
      continue;
    }

    ++checkedStyles;

    EXPECT_EQ(gathered.size(), checkoutCountOf(style->name()))
        << "the " << style->name() << " style";
  }

  EXPECT_GT(checkedStyles, 0U);
}

TEST_F(CTEST_FontAwesomeIcons, every_icon_points_at_an_existing_svg_file)
{
  for (const auto& icon : icons->all()) {
    ASSERT_NE(icon, nullptr);

    EXPECT_TRUE(std::filesystem::is_regular_file(icon->filePath()))
        << "no " << icon->filePath() << " file";
  }
}

TEST_F(CTEST_FontAwesomeIcons, the_generated_qt_manifest_lists_every_icon)
{
  const std::string manifest{CTEST_FontAwesomeIcons_QRC};

  if (!std::filesystem::is_regular_file(manifest)) {
    GTEST_SKIP() << "no " << manifest
                 << " manifest: the FONTAWESOME_GENERATE_FULL_MANIFESTS option"
                    " is off";
  }

  EXPECT_EQ(aliasesOf(manifest), gatheredAliases());
}

TEST_F(CTEST_FontAwesomeIcons,
       the_generated_gresource_manifest_lists_every_icon)
{
  const std::string manifest{CTEST_FontAwesomeIcons_GRESOURCE_XML};

  if (!std::filesystem::is_regular_file(manifest)) {
    GTEST_SKIP() << "no " << manifest
                 << " manifest: the FONTAWESOME_GENERATE_FULL_MANIFESTS option"
                    " is off";
  }

  EXPECT_EQ(aliasesOf(manifest), gatheredAliases());
}

TEST_F(CTEST_FontAwesomeIcons, the_icons_resolve_to_the_configured_resources)
{
  const auto icon = icons->all().front();

  ASSERT_NE(icon, nullptr);

  const auto qt = FontAwesomeQtResourcePath::create();
  const auto gres = FontAwesomeGResourcePath::create();

  EXPECT_EQ(qt->of(icon), ":" + qt->prefix() + "/" + icon->alias());
  EXPECT_EQ(gres->of(icon), gres->prefix() + "/" + icon->alias());
}

TEST_F(CTEST_FontAwesomeIcons, the_checkout_carries_its_license_file)
{
  EXPECT_TRUE(std::filesystem::is_regular_file(
      fontawesome_decls::FONTAWESOME_LICENSE_FILE));
}
