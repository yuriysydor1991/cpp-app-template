#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <set>
#include <string>

#include "src/fontawesome/styles/FontAwesomeBrandsStyle.h"
#include "src/fontawesome/styles/FontAwesomeRegularStyle.h"
#include "src/fontawesome/styles/FontAwesomeSolidStyle.h"
#include "src/fontawesome/styles/FontAwesomeStyles.h"

using namespace fontawesome;
using namespace testing;

/**
 * @brief Unit test of the Font Awesome styles registry and of the styles it
 * holds.
 *
 * Nothing here touches the checkout on the disk, so the whole suite covers the
 * naming the rest of the subsystem builds every icon path upon.
 */
class UTEST_FontAwesomeStyles : public Test
{
 public:
  UTEST_FontAwesomeStyles() : styles{FontAwesomeStyles::create()} {}

  IFontAwesomeStylesPtr styles;
};

TEST_F(UTEST_FontAwesomeStyles, create_gives_an_instance)
{
  EXPECT_NE(FontAwesomeStyles::create(), nullptr);
}

TEST_F(UTEST_FontAwesomeStyles, holds_the_three_free_distribution_styles)
{
  ASSERT_NE(styles, nullptr);

  std::set<std::string> names;

  for (const auto& style : styles->all()) {
    ASSERT_NE(style, nullptr);
    names.insert(style->name());
  }

  EXPECT_EQ(names, (std::set<std::string>{"brands", "regular", "solid"}));
}

TEST_F(UTEST_FontAwesomeStyles, every_style_names_an_own_webfont_file)
{
  std::set<std::string> webfonts;

  for (const auto& style : styles->all()) {
    ASSERT_NE(style, nullptr);
    EXPECT_FALSE(style->webfontFileName().empty());
    webfonts.insert(style->webfontFileName());
  }

  EXPECT_EQ(webfonts.size(), styles->all().size());
}

TEST_F(UTEST_FontAwesomeStyles, gives_the_style_of_the_requested_name)
{
  for (const auto& style : styles->all()) {
    ASSERT_NE(style, nullptr);

    const auto found = styles->byName(style->name());

    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->name(), style->name());
  }
}

TEST_F(UTEST_FontAwesomeStyles, gives_no_style_of_an_unknown_name)
{
  EXPECT_EQ(styles->byName("duotone"), nullptr);
  EXPECT_EQ(styles->byName({}), nullptr);
}

TEST_F(UTEST_FontAwesomeStyles, styles_name_themselves_and_their_webfonts)
{
  EXPECT_EQ(FontAwesomeSolidStyle::create()->name(), "solid");
  EXPECT_EQ(FontAwesomeSolidStyle::create()->webfontFileName(),
            "fa-solid-900.woff2");

  EXPECT_EQ(FontAwesomeRegularStyle::create()->name(), "regular");
  EXPECT_EQ(FontAwesomeRegularStyle::create()->webfontFileName(),
            "fa-regular-400.woff2");

  EXPECT_EQ(FontAwesomeBrandsStyle::create()->name(), "brands");
  EXPECT_EQ(FontAwesomeBrandsStyle::create()->webfontFileName(),
            "fa-brands-400.woff2");
}
