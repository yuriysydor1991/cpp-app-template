#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "src/freesoundaudio/FreesoundSound.h"
#include "src/freesoundaudio/categories/FreesoundCategory.h"
#include "src/freesoundaudio/resources/FreesoundGResourcePath.h"
#include "src/freesoundaudio/resources/FreesoundQtResourcePath.h"

using namespace freesoundaudio;
using namespace testing;

class UTEST_FreesoundResourcePath : public Test
{
 public:
  inline static const std::string expectedPrefix{"/sounds"};
  inline static const std::string expectedAlias{
      "interface-sounds/Audio/click_001.ogg"};

  FreesoundSoundPtr sound{FreesoundSound::create(
      FreesoundCategory::create("interface-sounds"), "Audio/click_001.ogg")};
};

TEST_F(UTEST_FreesoundResourcePath, keeps_an_already_normal_prefix)
{
  EXPECT_EQ(FreesoundQtResourcePath::create(expectedPrefix)->prefix(),
            expectedPrefix);
}

TEST_F(UTEST_FreesoundResourcePath, adds_the_missing_leading_slash)
{
  EXPECT_EQ(FreesoundQtResourcePath::create("sounds")->prefix(),
            expectedPrefix);
}

TEST_F(UTEST_FreesoundResourcePath, drops_the_trailing_slashes)
{
  EXPECT_EQ(FreesoundQtResourcePath::create("/sounds///")->prefix(),
            expectedPrefix);
}

TEST_F(UTEST_FreesoundResourcePath, an_empty_prefix_becomes_the_root_one)
{
  EXPECT_EQ(FreesoundQtResourcePath::create("")->prefix(), "/");
}

TEST_F(UTEST_FreesoundResourcePath, the_qt_path_carries_the_resource_mark)
{
  EXPECT_EQ(FreesoundQtResourcePath::create(expectedPrefix)->of(sound),
            ":" + expectedPrefix + "/" + expectedAlias);
}

TEST_F(UTEST_FreesoundResourcePath, the_qt_uri_carries_the_qrc_scheme)
{
  EXPECT_EQ(FreesoundQtResourcePath::create(expectedPrefix)->uriOf(sound),
            "qrc:" + expectedPrefix + "/" + expectedAlias);
}

TEST_F(UTEST_FreesoundResourcePath, the_gresource_path_is_the_prefixed_alias)
{
  EXPECT_EQ(FreesoundGResourcePath::create(expectedPrefix)->of(sound),
            expectedPrefix + "/" + expectedAlias);
}

TEST_F(UTEST_FreesoundResourcePath,
       the_gresource_uri_carries_the_resource_scheme)
{
  EXPECT_EQ(FreesoundGResourcePath::create(expectedPrefix)->uriOf(sound),
            "resource://" + expectedPrefix + "/" + expectedAlias);
}

TEST_F(UTEST_FreesoundResourcePath, no_sound_gives_no_path_at_all)
{
  auto qt = FreesoundQtResourcePath::create(expectedPrefix);
  auto gresource = FreesoundGResourcePath::create(expectedPrefix);

  EXPECT_TRUE(qt->of(nullptr).empty());
  EXPECT_TRUE(qt->uriOf(nullptr).empty());
  EXPECT_TRUE(gresource->of(nullptr).empty());
  EXPECT_TRUE(gresource->uriOf(nullptr).empty());
}
