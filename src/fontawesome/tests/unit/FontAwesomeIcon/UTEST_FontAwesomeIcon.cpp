#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "fontawesome-decls.h"
#include "src/fontawesome/FontAwesomeIcon.h"
#include "src/fontawesome/styles/FontAwesomeSolidStyle.h"

using namespace fontawesome;
using namespace testing;

/**
 * @brief Unit test of the names a single Font Awesome icon derives.
 *
 * Every generated resource manifest keys it's icons by the very alias checked
 * below, so the expectations here pin the single naming both the manifests and
 * the run time locators agree upon.
 */
class UTEST_FontAwesomeIcon : public Test
{
 public:
  UTEST_FontAwesomeIcon()
      : icon{FontAwesomeIcon::create(FontAwesomeSolidStyle::create(),
                                     "folder-open")}
  {
  }

  FontAwesomeIconPtr icon;
};

TEST_F(UTEST_FontAwesomeIcon, create_gives_an_instance)
{
  EXPECT_NE(icon, nullptr);
}

TEST_F(UTEST_FontAwesomeIcon, keeps_the_given_name_and_style)
{
  ASSERT_NE(icon, nullptr);
  ASSERT_NE(icon->style(), nullptr);

  EXPECT_EQ(icon->name(), "folder-open");
  EXPECT_EQ(icon->style()->name(), "solid");
}

TEST_F(UTEST_FontAwesomeIcon, derives_the_svg_file_name)
{
  EXPECT_EQ(icon->fileName(), "folder-open.svg");
}

TEST_F(UTEST_FontAwesomeIcon, derives_the_resource_alias)
{
  EXPECT_EQ(icon->alias(), "solid/folder-open.svg");
}

TEST_F(UTEST_FontAwesomeIcon, derives_the_checkout_relative_path)
{
  EXPECT_EQ(icon->relativePath(), "svgs/solid/folder-open.svg");
}

TEST_F(UTEST_FontAwesomeIcon, derives_the_configured_absolute_path)
{
  EXPECT_EQ(icon->filePath(),
            fontawesome_decls::FONTAWESOME_SVGS_DIR + "/solid/folder-open.svg");
}

TEST_F(UTEST_FontAwesomeIcon, icons_of_other_styles_keep_their_own_aliases)
{
  const auto other =
      FontAwesomeIcon::create(FontAwesomeSolidStyle::create(), "gear");

  ASSERT_NE(other, nullptr);

  EXPECT_EQ(other->alias(), "solid/gear.svg");
  EXPECT_NE(other->alias(), icon->alias());
}
