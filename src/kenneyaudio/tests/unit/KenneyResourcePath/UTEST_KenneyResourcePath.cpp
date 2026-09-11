#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "src/kenneyaudio/KenneySound.h"
#include "src/kenneyaudio/packs/KenneyPack.h"
#include "src/kenneyaudio/resources/KenneyGResourcePath.h"
#include "src/kenneyaudio/resources/KenneyQtResourcePath.h"

using namespace kenneyaudio;
using namespace testing;

class UTEST_KenneyResourcePath : public Test
{
 public:
  inline static const std::string expectedPrefix{"/sounds"};
  inline static const std::string expectedAlias{
      "interface-sounds/Audio/click_001.ogg"};

  KenneySoundPtr sound{KenneySound::create(
      KenneyPack::create("interface-sounds"), "Audio/click_001.ogg")};
};

TEST_F(UTEST_KenneyResourcePath, keeps_an_already_normal_prefix)
{
  EXPECT_EQ(KenneyQtResourcePath::create(expectedPrefix)->prefix(),
            expectedPrefix);
}

TEST_F(UTEST_KenneyResourcePath, adds_the_missing_leading_slash)
{
  EXPECT_EQ(KenneyQtResourcePath::create("sounds")->prefix(), expectedPrefix);
}

TEST_F(UTEST_KenneyResourcePath, drops_the_trailing_slashes)
{
  EXPECT_EQ(KenneyQtResourcePath::create("/sounds///")->prefix(),
            expectedPrefix);
}

TEST_F(UTEST_KenneyResourcePath, an_empty_prefix_becomes_the_root_one)
{
  EXPECT_EQ(KenneyQtResourcePath::create("")->prefix(), "/");
}

TEST_F(UTEST_KenneyResourcePath, the_qt_path_carries_the_resource_mark)
{
  EXPECT_EQ(KenneyQtResourcePath::create(expectedPrefix)->of(sound),
            ":" + expectedPrefix + "/" + expectedAlias);
}

TEST_F(UTEST_KenneyResourcePath, the_qt_uri_carries_the_qrc_scheme)
{
  EXPECT_EQ(KenneyQtResourcePath::create(expectedPrefix)->uriOf(sound),
            "qrc:" + expectedPrefix + "/" + expectedAlias);
}

TEST_F(UTEST_KenneyResourcePath, the_gresource_path_is_the_prefixed_alias)
{
  EXPECT_EQ(KenneyGResourcePath::create(expectedPrefix)->of(sound),
            expectedPrefix + "/" + expectedAlias);
}

TEST_F(UTEST_KenneyResourcePath, the_gresource_uri_carries_the_resource_scheme)
{
  EXPECT_EQ(KenneyGResourcePath::create(expectedPrefix)->uriOf(sound),
            "resource://" + expectedPrefix + "/" + expectedAlias);
}

TEST_F(UTEST_KenneyResourcePath, no_sound_gives_no_path_at_all)
{
  auto qt = KenneyQtResourcePath::create(expectedPrefix);
  auto gresource = KenneyGResourcePath::create(expectedPrefix);

  EXPECT_TRUE(qt->of(nullptr).empty());
  EXPECT_TRUE(qt->uriOf(nullptr).empty());
  EXPECT_TRUE(gresource->of(nullptr).empty());
  EXPECT_TRUE(gresource->uriOf(nullptr).empty());
}
