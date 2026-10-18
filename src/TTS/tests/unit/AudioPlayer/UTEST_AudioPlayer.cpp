#include <SDL.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include "src/TTS/AudioPlayer.h"

using namespace tts;
using namespace testing;

/**
 * @brief Unit test of the AudioPlayer over the demand only SDL audio drivers,
 * so no real device takes part: the dummy one plays the speech at the real
 * time pace into nowhere, while the disk one writes it into a file at once.
 */
class UTEST_AudioPlayer : public Test
{
 public:
  using clock = std::chrono::steady_clock;

  /// @brief Picks the SDL audio driver of the player. The variables of the
  /// SDL3 run sdl2-compat library are given as well.
  static void use_audio_driver(const char* const driver)
  {
    SDL_setenv("SDL_AUDIODRIVER", driver, 1);
    SDL_setenv("SDL_AUDIO_DRIVER", driver, 1);
  }

  /// @brief Makes the disk audio driver write the played audio into the
  /// given file with no delays.
  static void play_into_the_file(const std::string& outputFile)
  {
    use_audio_driver("disk");

    SDL_setenv("SDL_DISKAUDIOFILE", outputFile.c_str(), 1);
    SDL_setenv("SDL_AUDIO_DISK_OUTPUT_FILE", outputFile.c_str(), 1);
    SDL_setenv("SDL_DISKAUDIODELAY", "0", 1);
    SDL_setenv("SDL_AUDIO_DISK_TIMESCALE", "0.01", 1);
  }

  /// @brief The speech of the given duration, a sawtooth rather than the
  /// silence.
  static Speech speech_of(const std::chrono::milliseconds duration)
  {
    Speech::samples pcm(static_cast<std::size_t>(SAMPLE_RATE) *
                        static_cast<std::size_t>(duration.count()) / 1000U);

    for (std::size_t index = 0U; index < pcm.size(); ++index) {
      pcm[index] = static_cast<Speech::sample>((index % 100U) * 300U);
    }

    return Speech{pcm, SAMPLE_RATE};
  }

  inline static constexpr const int SAMPLE_RATE = 22050;
  inline static const AudioPlayer::stop_check NEVER{[] { return false; }};

  AudioPlayer player;
};

TEST_F(UTEST_AudioPlayer, create_gives_an_instance)
{
  EXPECT_NE(AudioPlayer::create(), nullptr);
}

TEST_F(UTEST_AudioPlayer, the_dummy_driver_plays_the_whole_speech)
{
  use_audio_driver("dummy");

  const auto speech = speech_of(std::chrono::milliseconds{500});
  const auto start = clock::now();

  EXPECT_TRUE(player.play(speech, NEVER));

  // The dummy driver takes the audio at the real time pace.
  EXPECT_GE(clock::now() - start, speech.get_duration() / 2);
}

TEST_F(UTEST_AudioPlayer, an_empty_stop_check_plays_the_whole_speech)
{
  use_audio_driver("dummy");

  const auto speech = speech_of(std::chrono::milliseconds{300});
  const auto start = clock::now();

  EXPECT_TRUE(player.play(speech, {}));
  EXPECT_GE(clock::now() - start, speech.get_duration() / 2);
}

TEST_F(UTEST_AudioPlayer, the_stop_check_cuts_the_playback)
{
  use_audio_driver("dummy");

  const auto speech = speech_of(std::chrono::seconds{10});
  const auto start = clock::now();

  EXPECT_TRUE(player.play(speech, [] { return true; }));
  EXPECT_LT(clock::now() - start, std::chrono::seconds{5});
}

TEST_F(UTEST_AudioPlayer, the_disk_driver_gets_the_speech)
{
  const std::string path{UTEST_AudioPlayer_DATA_DIR "/played.raw"};

  std::filesystem::remove(path);
  play_into_the_file(path);

  const auto speech = speech_of(std::chrono::milliseconds{200});

  ASSERT_TRUE(player.play(speech, NEVER));

  std::ifstream file{path, std::ifstream::binary};
  const std::vector<char> played{std::istreambuf_iterator<char>{file},
                                 std::istreambuf_iterator<char>{}};

  // The SDL2 writes the very samples, while the SDL3 behind the sdl2-compat
  // converts them into the format of it's own, so the size and the sound are
  // checked alone.
  EXPECT_GE(played.size(),
            speech.get_samples().size() * sizeof(Speech::sample));
  EXPECT_TRUE(std::any_of(played.cbegin(), played.cend(),
                          [](const char byte) { return byte != 0; }));
}

TEST_F(UTEST_AudioPlayer, an_empty_speech_plays_nothing)
{
  use_audio_driver("dummy");

  EXPECT_TRUE(player.play(Speech{{}, SAMPLE_RATE}, NEVER));
}

TEST_F(UTEST_AudioPlayer, an_unknown_driver_fails_the_playback)
{
  use_audio_driver("nosuchdriver");

  EXPECT_FALSE(player.play(speech_of(std::chrono::milliseconds{100}), NEVER));
}
