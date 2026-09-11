#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/opengameartaudio/sounds/OpenGameArtSounds.h"

using namespace opengameartaudio;
using namespace testing;

class UTEST_OpenGameArtSounds : public Test
{
 public:
  IOpenGameArtSoundsPtr sounds{OpenGameArtSounds::create()};
};

TEST_F(UTEST_OpenGameArtSounds, carries_every_sound_of_every_pack)
{
  EXPECT_EQ(sounds->count(), 3u);
  EXPECT_EQ(sounds->all().size(), sounds->count());
}

TEST_F(UTEST_OpenGameArtSounds, gives_the_sounds_of_a_single_pack)
{
  const auto ofInterface = sounds->ofPack("interface-sounds");

  EXPECT_EQ(ofInterface.size(), 2u);

  for (const auto& sound : ofInterface) {
    EXPECT_EQ(sound->pack()->name(), "interface-sounds");
  }
}

TEST_F(UTEST_OpenGameArtSounds, gives_no_sounds_of_an_unknown_pack)
{
  EXPECT_TRUE(sounds->ofPack("no-such-pack").empty());
}

TEST_F(UTEST_OpenGameArtSounds, finds_a_sound_by_it_s_pack_and_path)
{
  auto found = sounds->find("interface-sounds", "Audio/click_001.ogg");

  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found->name(), "click_001");
  EXPECT_EQ(found->alias(), "interface-sounds/Audio/click_001.ogg");
}

TEST_F(UTEST_OpenGameArtSounds, gives_no_sound_of_an_unknown_path)
{
  EXPECT_EQ(sounds->find("interface-sounds", "Audio/no_such.ogg"), nullptr);
}

TEST_F(UTEST_OpenGameArtSounds, searches_the_sounds_by_a_name_part)
{
  const auto found = sounds->search("click");

  ASSERT_EQ(found.size(), 1u);
  EXPECT_EQ(found.front()->name(), "click_001");
}

TEST_F(UTEST_OpenGameArtSounds, a_search_reaches_every_pack)
{
  EXPECT_EQ(sounds->search("_").size(), sounds->count());
}

TEST_F(UTEST_OpenGameArtSounds, an_unmatched_search_gives_nothing)
{
  EXPECT_TRUE(sounds->search("no-such-sound").empty());
}

TEST_F(UTEST_OpenGameArtSounds, a_set_with_no_packs_stays_empty)
{
  auto empty = OpenGameArtSounds::create(nullptr);

  EXPECT_EQ(empty->count(), 0u);
  EXPECT_TRUE(empty->all().empty());
}
