#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>

#include "src/freesoundaudio/player/FreesoundRandomSound.h"
#include "src/freesoundaudio/player/FreesoundSdlSoundPlayer.h"
#include "src/freesoundaudio/sounds/FreesoundSounds.h"

using namespace freesoundaudio;
using namespace testing;

// Answers for the player against the categories the project has really been
// configured with. The SDL_AUDIODRIVER environment variable is pinned to the
// dummy driver by the CMake test properties, so the sound is really decoded,
// queued and drained on a machine carrying no sound card at all.
class CTEST_FreesoundSoundPlayer : public Test
{
 public:
  IFreesoundSoundsPtr sounds{FreesoundSounds::create()};
  IFreesoundSoundPlayerPtr player{FreesoundSdlSoundPlayer::create()};
  FreesoundRandomSound drawn{20260911};
};

TEST_F(CTEST_FreesoundSoundPlayer, the_player_comes_up)
{
  ASSERT_NE(player, nullptr);
}

TEST_F(CTEST_FreesoundSoundPlayer, the_bare_sdl2_covers_the_wave_files_alone)
{
  EXPECT_TRUE(player->supports("wav"));
  EXPECT_FALSE(player->supports("ogg"));
  EXPECT_FALSE(player->supports("mp3"));
  EXPECT_FALSE(player->supports(""));
}

TEST_F(CTEST_FreesoundSoundPlayer, a_format_the_backend_misses_is_refused)
{
  auto compressed = drawn.pick(sounds, "ogg");

  if (compressed == nullptr) {
    GTEST_SKIP() << "The configured categories carry no .ogg sound";
  }

  EXPECT_FALSE(player->play(compressed));
}

TEST_F(CTEST_FreesoundSoundPlayer, a_drawn_wave_sound_really_plays)
{
  auto sound = drawn.pick(sounds, "wav");

  if (sound == nullptr) {
    GTEST_SKIP() << "The configured categories carry no .wav sound";
  }

  std::ifstream soundFile{sound->filePath(), std::ios::binary};

  ASSERT_TRUE(soundFile.good()) << "No " << sound->filePath() << " sound file";

  EXPECT_TRUE(player->play(sound)) << "Fail to play " << sound->alias();
}
