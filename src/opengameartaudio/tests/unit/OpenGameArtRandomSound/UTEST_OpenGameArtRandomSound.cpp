#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <set>
#include <string>

#include "src/opengameartaudio/player/OpenGameArtRandomSound.h"
#include "src/opengameartaudio/sounds/OpenGameArtSounds.h"

using namespace opengameartaudio;
using namespace testing;

class UTEST_OpenGameArtRandomSound : public Test
{
 public:
  inline static constexpr OpenGameArtRandomSound::Seed expectedSeed{20260911};

  IOpenGameArtSoundsPtr sounds{OpenGameArtSounds::create()};
};

TEST_F(UTEST_OpenGameArtRandomSound, draws_a_sound_of_the_given_set)
{
  OpenGameArtRandomSound drawn{expectedSeed};

  auto sound = drawn.pick(sounds);

  ASSERT_NE(sound, nullptr);
  EXPECT_NE(sounds->find(sound->pack()->name(), sound->path()), nullptr);
}

TEST_F(UTEST_OpenGameArtRandomSound, the_same_seed_draws_the_same_sounds)
{
  OpenGameArtRandomSound first{expectedSeed};
  OpenGameArtRandomSound second{expectedSeed};

  for (int draw = 0; draw < 8; ++draw) {
    EXPECT_EQ(first.pick(sounds)->alias(), second.pick(sounds)->alias());
  }
}

TEST_F(UTEST_OpenGameArtRandomSound, the_draws_reach_more_than_a_single_sound)
{
  OpenGameArtRandomSound drawn{expectedSeed};

  std::set<std::string> aliases;

  for (int draw = 0; draw < 64; ++draw) {
    aliases.insert(drawn.pick(sounds)->alias());
  }

  EXPECT_GT(aliases.size(), 1u);
}

TEST_F(UTEST_OpenGameArtRandomSound, narrows_the_draw_to_a_file_extension)
{
  OpenGameArtRandomSound drawn{expectedSeed};

  for (int draw = 0; draw < 16; ++draw) {
    auto sound = drawn.pick(sounds, "wav");

    ASSERT_NE(sound, nullptr);
    EXPECT_EQ(sound->extension(), "wav");
  }
}

TEST_F(UTEST_OpenGameArtRandomSound, gives_no_sound_of_an_absent_extension)
{
  OpenGameArtRandomSound drawn{expectedSeed};

  EXPECT_EQ(drawn.pick(sounds, "no-such-extension"), nullptr);
}

TEST_F(UTEST_OpenGameArtRandomSound, an_empty_or_absent_set_draws_nothing)
{
  OpenGameArtRandomSound drawn{expectedSeed};

  EXPECT_EQ(drawn.pick(nullptr), nullptr);
  EXPECT_EQ(drawn.pick(nullptr, "wav"), nullptr);
  EXPECT_EQ(drawn.pick(OpenGameArtSounds::create(nullptr)), nullptr);
}
