#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <set>
#include <string>

#include "src/kenneyaudio/player/KenneyRandomSound.h"
#include "src/kenneyaudio/sounds/KenneySounds.h"

using namespace kenneyaudio;
using namespace testing;

class UTEST_KenneyRandomSound : public Test
{
 public:
  inline static constexpr KenneyRandomSound::Seed expectedSeed{20260911};

  IKenneySoundsPtr sounds{KenneySounds::create()};
};

TEST_F(UTEST_KenneyRandomSound, draws_a_sound_of_the_given_set)
{
  KenneyRandomSound drawn{expectedSeed};

  auto sound = drawn.pick(sounds);

  ASSERT_NE(sound, nullptr);
  EXPECT_NE(sounds->find(sound->pack()->name(), sound->path()), nullptr);
}

TEST_F(UTEST_KenneyRandomSound, the_same_seed_draws_the_same_sounds)
{
  KenneyRandomSound first{expectedSeed};
  KenneyRandomSound second{expectedSeed};

  for (int draw = 0; draw < 8; ++draw) {
    EXPECT_EQ(first.pick(sounds)->alias(), second.pick(sounds)->alias());
  }
}

TEST_F(UTEST_KenneyRandomSound, the_draws_reach_more_than_a_single_sound)
{
  KenneyRandomSound drawn{expectedSeed};

  std::set<std::string> aliases;

  for (int draw = 0; draw < 64; ++draw) {
    aliases.insert(drawn.pick(sounds)->alias());
  }

  EXPECT_GT(aliases.size(), 1u);
}

TEST_F(UTEST_KenneyRandomSound, narrows_the_draw_to_a_file_extension)
{
  KenneyRandomSound drawn{expectedSeed};

  for (int draw = 0; draw < 16; ++draw) {
    auto sound = drawn.pick(sounds, "wav");

    ASSERT_NE(sound, nullptr);
    EXPECT_EQ(sound->extension(), "wav");
  }
}

TEST_F(UTEST_KenneyRandomSound, gives_no_sound_of_an_absent_extension)
{
  KenneyRandomSound drawn{expectedSeed};

  EXPECT_EQ(drawn.pick(sounds, "no-such-extension"), nullptr);
}

TEST_F(UTEST_KenneyRandomSound, an_empty_or_absent_set_draws_nothing)
{
  KenneyRandomSound drawn{expectedSeed};

  EXPECT_EQ(drawn.pick(nullptr), nullptr);
  EXPECT_EQ(drawn.pick(nullptr, "wav"), nullptr);
  EXPECT_EQ(drawn.pick(KenneySounds::create(nullptr)), nullptr);
}
