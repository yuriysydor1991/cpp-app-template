#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "src/opengameartaudio/OpenGameArtSound.h"
#include "src/opengameartaudio/packs/OpenGameArtPack.h"
#include "src/opengameartaudio/resources/OpenGameArtGResourcePath.h"
#include "src/opengameartaudio/resources/OpenGameArtQtResourcePath.h"

using namespace opengameartaudio;
using namespace testing;

class UTEST_OpenGameArtResourcePath : public Test
{
 public:
  inline static const std::string expectedPrefix{"/sounds"};
  inline static const std::string expectedAlias{
      "interface-sounds/Audio/click_001.ogg"};

  OpenGameArtSoundPtr sound{OpenGameArtSound::create(
      OpenGameArtPack::create("interface-sounds", "CC0-1.0"),
      "Audio/click_001.ogg")};
};

TEST_F(UTEST_OpenGameArtResourcePath, keeps_an_already_normal_prefix)
{
  EXPECT_EQ(OpenGameArtQtResourcePath::create(expectedPrefix)->prefix(),
            expectedPrefix);
}

TEST_F(UTEST_OpenGameArtResourcePath, adds_the_missing_leading_slash)
{
  EXPECT_EQ(OpenGameArtQtResourcePath::create("sounds")->prefix(),
            expectedPrefix);
}

TEST_F(UTEST_OpenGameArtResourcePath, drops_the_trailing_slashes)
{
  EXPECT_EQ(OpenGameArtQtResourcePath::create("/sounds///")->prefix(),
            expectedPrefix);
}

TEST_F(UTEST_OpenGameArtResourcePath, an_empty_prefix_becomes_the_root_one)
{
  EXPECT_EQ(OpenGameArtQtResourcePath::create("")->prefix(), "/");
}

TEST_F(UTEST_OpenGameArtResourcePath, the_qt_path_carries_the_resource_mark)
{
  EXPECT_EQ(OpenGameArtQtResourcePath::create(expectedPrefix)->of(sound),
            ":" + expectedPrefix + "/" + expectedAlias);
}

TEST_F(UTEST_OpenGameArtResourcePath, the_qt_uri_carries_the_qrc_scheme)
{
  EXPECT_EQ(OpenGameArtQtResourcePath::create(expectedPrefix)->uriOf(sound),
            "qrc:" + expectedPrefix + "/" + expectedAlias);
}

TEST_F(UTEST_OpenGameArtResourcePath, the_gresource_path_is_the_prefixed_alias)
{
  EXPECT_EQ(OpenGameArtGResourcePath::create(expectedPrefix)->of(sound),
            expectedPrefix + "/" + expectedAlias);
}

TEST_F(UTEST_OpenGameArtResourcePath,
       the_gresource_uri_carries_the_resource_scheme)
{
  EXPECT_EQ(OpenGameArtGResourcePath::create(expectedPrefix)->uriOf(sound),
            "resource://" + expectedPrefix + "/" + expectedAlias);
}

TEST_F(UTEST_OpenGameArtResourcePath, no_sound_gives_no_path_at_all)
{
  auto qt = OpenGameArtQtResourcePath::create(expectedPrefix);
  auto gresource = OpenGameArtGResourcePath::create(expectedPrefix);

  EXPECT_TRUE(qt->of(nullptr).empty());
  EXPECT_TRUE(qt->uriOf(nullptr).empty());
  EXPECT_TRUE(gresource->of(nullptr).empty());
  EXPECT_TRUE(gresource->uriOf(nullptr).empty());
}
