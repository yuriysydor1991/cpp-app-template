#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>

#include "src/opengameartaudio/player/OpenGameArtRandomSound.h"
#include "src/opengameartaudio/player/OpenGameArtSdlMixerSoundPlayer.h"
#include "src/opengameartaudio/sounds/OpenGameArtSounds.h"

using namespace opengameartaudio;
using namespace testing;

// Answers for the player against the packs the project has really been
// configured with. The SDL_AUDIODRIVER environment variable is pinned to the
// dummy driver by the CMake test properties, so the sound is really decoded,
// mixed and drained on a machine carrying no sound card at all.
class CTEST_OpenGameArtSoundPlayer : public Test
{
 public:
  IOpenGameArtSoundsPtr sounds{OpenGameArtSounds::create()};
  IOpenGameArtSoundPlayerPtr player{OpenGameArtSdlMixerSoundPlayer::create()};
  OpenGameArtRandomSound drawn{20260911};
};

TEST_F(CTEST_OpenGameArtSoundPlayer, the_player_comes_up)
{
  ASSERT_NE(player, nullptr);
}

TEST_F(CTEST_OpenGameArtSoundPlayer, the_shipped_formats_are_covered)
{
  EXPECT_TRUE(player->supports("wav"));
  EXPECT_TRUE(player->supports("ogg"));
}

TEST_F(CTEST_OpenGameArtSoundPlayer, a_format_the_decoders_miss_is_refused)
{
  EXPECT_FALSE(player->supports("mid"));
  EXPECT_FALSE(player->supports(""));
}

TEST_F(CTEST_OpenGameArtSoundPlayer, a_drawn_compressed_sound_really_plays)
{
  auto sound = drawn.pick(sounds, "ogg");

  if (sound == nullptr) {
    GTEST_SKIP() << "The configured packs carry no .ogg sound";
  }

  std::ifstream soundFile{sound->filePath(), std::ios::binary};

  ASSERT_TRUE(soundFile.good()) << "No " << sound->filePath() << " sound file";

  EXPECT_TRUE(player->play(sound)) << "Fail to play " << sound->alias();
}

TEST_F(CTEST_OpenGameArtSoundPlayer, a_drawn_wave_sound_really_plays)
{
  auto sound = drawn.pick(sounds, "wav");

  if (sound == nullptr) {
    GTEST_SKIP() << "The configured packs carry no .wav sound";
  }

  std::ifstream soundFile{sound->filePath(), std::ios::binary};

  ASSERT_TRUE(soundFile.good()) << "No " << sound->filePath() << " sound file";

  EXPECT_TRUE(player->play(sound)) << "Fail to play " << sound->alias();
}
