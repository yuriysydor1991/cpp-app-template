#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "fontawesome-decls.h"
#include "src/fontawesome/FontAwesomeIcon.h"
#include "src/fontawesome/resources/FontAwesomeGResourcePath.h"
#include "src/fontawesome/resources/FontAwesomeQtResourcePath.h"
#include "src/fontawesome/styles/FontAwesomeSolidStyle.h"

using namespace fontawesome;
using namespace testing;

/**
 * @brief Unit test of the run time locators of the icons embedded into the
 * resource system of a GUI toolkit.
 *
 * The paths checked below are the ones a Qt or a Gtkmm branch of the template
 * hands over to it's widgets, so they have to match the aliases the generated
 * resource manifests carry.
 */
class UTEST_FontAwesomeResourcePath : public Test
{
 public:
  UTEST_FontAwesomeResourcePath()
      : icon{FontAwesomeIcon::create(FontAwesomeSolidStyle::create(),
                                     "folder-open")}
  {
  }

  FontAwesomeIconPtr icon;
};

TEST_F(UTEST_FontAwesomeResourcePath, create_gives_the_instances)
{
  EXPECT_NE(FontAwesomeQtResourcePath::create(), nullptr);
  EXPECT_NE(FontAwesomeGResourcePath::create(), nullptr);
}

TEST_F(UTEST_FontAwesomeResourcePath, take_the_configured_prefixes_by_default)
{
  EXPECT_EQ(FontAwesomeQtResourcePath::create()->prefix(),
            fontawesome_decls::FONTAWESOME_QT_RESOURCE_PREFIX);
  EXPECT_EQ(FontAwesomeGResourcePath::create()->prefix(),
            fontawesome_decls::FONTAWESOME_GRESOURCE_PREFIX);
}

TEST_F(UTEST_FontAwesomeResourcePath, qt_paths_carry_the_resource_mark)
{
  const auto qt = FontAwesomeQtResourcePath::create("/icons");

  EXPECT_EQ(qt->of(icon), ":/icons/solid/folder-open.svg");
  EXPECT_EQ(qt->uriOf(icon), "qrc:/icons/solid/folder-open.svg");
}

TEST_F(UTEST_FontAwesomeResourcePath, gresource_paths_carry_the_plain_prefix)
{
  const auto gres = FontAwesomeGResourcePath::create("/ua/org/kytok/icons");

  EXPECT_EQ(gres->of(icon), "/ua/org/kytok/icons/solid/folder-open.svg");
  EXPECT_EQ(gres->uriOf(icon),
            "resource:///ua/org/kytok/icons/solid/folder-open.svg");
}

TEST_F(UTEST_FontAwesomeResourcePath, prefixes_get_normalized)
{
  EXPECT_EQ(FontAwesomeQtResourcePath::create("icons/")->prefix(), "/icons");
  EXPECT_EQ(FontAwesomeQtResourcePath::create("/icons///")->prefix(), "/icons");
  EXPECT_EQ(FontAwesomeQtResourcePath::create({})->prefix(), "/");
  EXPECT_EQ(FontAwesomeGResourcePath::create("a/b")->prefix(), "/a/b");
}

TEST_F(UTEST_FontAwesomeResourcePath, no_icon_gives_no_path)
{
  const auto qt = FontAwesomeQtResourcePath::create();
  const auto gres = FontAwesomeGResourcePath::create();

  EXPECT_TRUE(qt->of({}).empty());
  EXPECT_TRUE(qt->uriOf({}).empty());
  EXPECT_TRUE(gres->of({}).empty());
  EXPECT_TRUE(gres->uriOf({}).empty());
}
