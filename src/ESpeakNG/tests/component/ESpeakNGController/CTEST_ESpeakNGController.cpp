#include <SDL.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>

#include "src/ESpeakNG/ESpeakNGController.h"
#include "src/TTS/AudioPlayer.h"
#include "src/TTS/Speech.h"
#include "src/TTS/WavWriter.h"
#include "src/log/log.h"
#include "src/log/severity-macro-consts.h"

using namespace espeakng;
using namespace testing;

/**
 * @brief Component test of the ESpeakNGController driving the real eSpeak NG
 * library together with the WAV file and the SDL2 playback outputs of the
 * speech. The dummy audio driver of the SDL plays the speech, so no sound card
 * takes part. The errors alone are checked in the log, since the builds of the
 * lower MAX_LOG_LEVEL values drop the rest.
 */
class CTEST_ESpeakNGController : public Test
{
 public:
  CTEST_ESpeakNGController()
  {
    std::ofstream truncating{logFile, std::ofstream::trunc};

    LOG_INIT(logFile, MACRO_LVL_TRACE, false);
  }

  /// @brief Reopens the log file to flush it, since the logger flushes the
  /// warnings and the errors alone, and gives the log written so far.
  std::string log_contents() const
  {
    LOG_INIT(logFile, MACRO_LVL_TRACE, false);

    std::stringstream contents;

    contents << std::ifstream{logFile}.rdbuf();

    return contents.str();
  }

  /// @brief Writes the given speech into a WAV file and reads it back with
  /// the SDL2, checking the format of it.
  tts::Speech::samples written_and_loaded(const tts::Speech& speech) const
  {
    EXPECT_TRUE(tts::WavWriter{}.write(speech, wavFile));

    SDL_AudioSpec spec{};
    Uint8* wave{nullptr};
    Uint32 length{0U};

    if (SDL_LoadWAV(wavFile.c_str(), &spec, &wave, &length) == nullptr) {
      ADD_FAILURE() << "The SDL fails to load the WAV: " << SDL_GetError();
      return {};
    }

    EXPECT_EQ(spec.freq, speech.get_sample_rate());
    EXPECT_EQ(spec.format, AUDIO_S16LSB);
    EXPECT_EQ(spec.channels, 1U);

    tts::Speech::samples pcm(length / sizeof(tts::Speech::sample));

    std::memcpy(pcm.data(), wave, pcm.size() * sizeof(tts::Speech::sample));
    SDL_FreeWAV(wave);

    return pcm;
  }

  /// @brief Tells if the given samples carry a sound rather than the silence.
  static bool sounds(const tts::Speech::samples& pcm)
  {
    return std::any_of(pcm.cbegin(), pcm.cend(), [](const auto sample) {
      return sample > 1000 || sample < -1000;
    });
  }

  /// @brief The eSpeak NG voices speak at the 22.05 kHz rate.
  inline static constexpr const int SAMPLE_RATE = 22050;

  const std::string logFile{CTEST_ESpeakNGController_DATA_DIR
                            "/CTEST_ESpeakNGController.log"};
  const std::string wavFile{CTEST_ESpeakNGController_DATA_DIR "/speech.wav"};

  ESpeakNGController controller;
};

TEST_F(CTEST_ESpeakNGController, english_speech_gets_into_the_wav_file)
{
  const auto speech = controller.synthesize("Hello, eSpeak NG!", "en");

  ASSERT_TRUE(speech.has_value());
  EXPECT_EQ(speech->get_sample_rate(), SAMPLE_RATE);
  EXPECT_GT(speech->get_duration().count(), 500);
  EXPECT_TRUE(sounds(speech->get_samples()));

  EXPECT_EQ(written_and_loaded(*speech), speech->get_samples());
}

TEST_F(CTEST_ESpeakNGController, ukrainian_voice_speaks_the_ukrainian_text)
{
  const auto speech = controller.synthesize("Привіт, світе!", "uk");

  ASSERT_TRUE(speech.has_value());
  EXPECT_GT(speech->get_duration().count(), 500);
  EXPECT_TRUE(sounds(speech->get_samples()));
}

TEST_F(CTEST_ESpeakNGController, longer_text_gives_longer_speech)
{
  const auto shorter = controller.synthesize("One.", "en");
  const auto longer = controller.synthesize("One, two, three, four.", "en");

  ASSERT_TRUE(shorter.has_value());
  ASSERT_TRUE(longer.has_value());
  EXPECT_GT(longer->get_duration(), shorter->get_duration());
}

TEST_F(CTEST_ESpeakNGController, unknown_voice_is_logged)
{
  EXPECT_FALSE(controller.synthesize("Hello", "nosuchvoice").has_value());

  EXPECT_THAT(log_contents(),
              HasSubstr("Fail to select the nosuchvoice eSpeak NG voice"));

  // The controller stays usable with a known voice.
  EXPECT_TRUE(controller.synthesize("Hello", "en").has_value());
}

TEST_F(CTEST_ESpeakNGController, speech_plays_through_the_dummy_driver)
{
  SDL_setenv("SDL_AUDIODRIVER", "dummy", 1);
  SDL_setenv("SDL_AUDIO_DRIVER", "dummy", 1);

  const auto speech = controller.synthesize("Hi!", "en");

  ASSERT_TRUE(speech.has_value());
  EXPECT_TRUE(tts::AudioPlayer{}.play(*speech, [] { return false; }));
}
