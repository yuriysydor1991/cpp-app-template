#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstddef>
#include <numeric>
#include <set>
#include <string>

#include "src/fontawesome/icons/FontAwesomeGeneratedIcons.h"
#include "src/fontawesome/icons/FontAwesomeIcons.h"
#include "src/fontawesome/styles/FontAwesomeStyles.h"

using namespace fontawesome;
using namespace testing;

/**
 * @brief Unit test of the whole icon set gathering.
 *
 * The generated icon names index is mocked here (see the
 * app/tests/mocks/FontAwesomeGeneratedIcons one), so the expectations below
 * hold no matter which Font Awesome release the project has been configured
 * with. The real index is driven by the CTEST_FontAwesomeIcons component test.
 */
class UTEST_FontAwesomeIcons : public Test
{
 public:
  UTEST_FontAwesomeIcons() : icons{FontAwesomeIcons::create()} {}

  static std::size_t mockedCount()
  {
    const auto& mocked = FontAwesomeGeneratedIcons::MOCKED_NAMES;

    return std::accumulate(mocked.cbegin(), mocked.cend(), std::size_t{0},
                           [](const std::size_t sum, const auto& style) {
                             return sum + style.second.size();
                           });
  }

  IFontAwesomeIconsPtr icons;
};

TEST_F(UTEST_FontAwesomeIcons, create_gives_an_instance)
{
  EXPECT_NE(FontAwesomeIcons::create(), nullptr);
}

TEST_F(UTEST_FontAwesomeIcons, gathers_every_icon_of_every_style)
{
  ASSERT_NE(icons, nullptr);

  EXPECT_EQ(icons->count(), mockedCount());
  EXPECT_EQ(icons->all().size(), icons->count());
}

TEST_F(UTEST_FontAwesomeIcons, gives_the_icons_of_the_requested_style)
{
  const auto solid = icons->ofStyle("solid");

  EXPECT_EQ(solid.size(), FontAwesomeGeneratedIcons::names("solid").size());

  for (const auto& icon : solid) {
    ASSERT_NE(icon, nullptr);
    ASSERT_NE(icon->style(), nullptr);
    EXPECT_EQ(icon->style()->name(), "solid");
  }
}

TEST_F(UTEST_FontAwesomeIcons, gives_no_icons_of_an_unknown_style)
{
  EXPECT_TRUE(icons->ofStyle("duotone").empty());
  EXPECT_TRUE(icons->ofStyle({}).empty());
}

TEST_F(UTEST_FontAwesomeIcons, finds_the_icon_of_the_requested_style_and_name)
{
  const auto icon = icons->find("solid", "folder-open");

  ASSERT_NE(icon, nullptr);

  EXPECT_EQ(icon->name(), "folder-open");
  EXPECT_EQ(icon->alias(), "solid/folder-open.svg");
}

TEST_F(UTEST_FontAwesomeIcons, finds_no_icon_of_a_wrong_style_or_name)
{
  EXPECT_EQ(icons->find("brands", "folder-open"), nullptr);
  EXPECT_EQ(icons->find("solid", "no-such-icon"), nullptr);
  EXPECT_EQ(icons->find({}, {}), nullptr);
}

TEST_F(UTEST_FontAwesomeIcons, searches_the_icons_by_a_name_part)
{
  const auto found = icons->search("git");

  std::set<std::string> aliases;

  for (const auto& icon : found) {
    ASSERT_NE(icon, nullptr);
    aliases.insert(icon->alias());
  }

  EXPECT_EQ(aliases,
            (std::set<std::string>{"brands/github.svg", "brands/gitlab.svg"}));
}

TEST_F(UTEST_FontAwesomeIcons, searches_nothing_by_an_empty_name_part)
{
  EXPECT_TRUE(icons->search({}).empty());
}

TEST_F(UTEST_FontAwesomeIcons, every_gathered_icon_carries_an_unique_alias)
{
  std::set<std::string> aliases;

  for (const auto& icon : icons->all()) {
    ASSERT_NE(icon, nullptr);
    aliases.insert(icon->alias());
  }

  EXPECT_EQ(aliases.size(), icons->count());
}
