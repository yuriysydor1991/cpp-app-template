#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <set>
#include <string>

#include "src/freesoundaudio/player/FreesoundRandomSound.h"
#include "src/freesoundaudio/sounds/FreesoundSounds.h"

using namespace freesoundaudio;
using namespace testing;

class UTEST_FreesoundRandomSound : public Test
{
 public:
  inline static constexpr FreesoundRandomSound::Seed expectedSeed{20260911};

  IFreesoundSoundsPtr sounds{FreesoundSounds::create()};
};

TEST_F(UTEST_FreesoundRandomSound, draws_a_sound_of_the_given_set)
{
  FreesoundRandomSound drawn{expectedSeed};

  auto sound = drawn.pick(sounds);

  ASSERT_NE(sound, nullptr);
  EXPECT_NE(sounds->find(sound->category()->name(), sound->path()), nullptr);
}

TEST_F(UTEST_FreesoundRandomSound, the_same_seed_draws_the_same_sounds)
{
  FreesoundRandomSound first{expectedSeed};
  FreesoundRandomSound second{expectedSeed};

  for (int draw = 0; draw < 8; ++draw) {
    EXPECT_EQ(first.pick(sounds)->alias(), second.pick(sounds)->alias());
  }
}

TEST_F(UTEST_FreesoundRandomSound, the_draws_reach_more_than_a_single_sound)
{
  FreesoundRandomSound drawn{expectedSeed};

  std::set<std::string> aliases;

  for (int draw = 0; draw < 64; ++draw) {
    aliases.insert(drawn.pick(sounds)->alias());
  }

  EXPECT_GT(aliases.size(), 1u);
}

TEST_F(UTEST_FreesoundRandomSound, narrows_the_draw_to_a_file_extension)
{
  FreesoundRandomSound drawn{expectedSeed};

  for (int draw = 0; draw < 16; ++draw) {
    auto sound = drawn.pick(sounds, "wav");

    ASSERT_NE(sound, nullptr);
    EXPECT_EQ(sound->extension(), "wav");
  }
}

TEST_F(UTEST_FreesoundRandomSound, gives_no_sound_of_an_absent_extension)
{
  FreesoundRandomSound drawn{expectedSeed};

  EXPECT_EQ(drawn.pick(sounds, "no-such-extension"), nullptr);
}

TEST_F(UTEST_FreesoundRandomSound, an_empty_or_absent_set_draws_nothing)
{
  FreesoundRandomSound drawn{expectedSeed};

  EXPECT_EQ(drawn.pick(nullptr), nullptr);
  EXPECT_EQ(drawn.pick(nullptr, "wav"), nullptr);
  EXPECT_EQ(drawn.pick(FreesoundSounds::create(nullptr)), nullptr);
}
