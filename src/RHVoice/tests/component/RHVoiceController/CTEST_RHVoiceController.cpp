#include <SDL.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>

#include "src/RHVoice/RHVoiceController.h"
#include "src/TTS/AudioPlayer.h"
#include "src/TTS/Speech.h"
#include "src/TTS/WavWriter.h"
#include "src/log/log.h"
#include "src/log/severity-macro-consts.h"

using namespace rhvoice;
using namespace testing;

/**
 * @brief Component test of the RHVoiceController driving the real RHVoice
 * library and voices together with the WAV file and the SDL2 playback outputs
 * of the speech. The dummy audio driver of the SDL plays the speech, so no
 * sound card takes part. The errors alone are checked in the log, since the
 * builds of the lower MAX_LOG_LEVEL values drop the rest.
 */
class CTEST_RHVoiceController : public Test
{
 public:
  CTEST_RHVoiceController()
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

  /// @brief The Alan, Anatol and Natalia voices speak at the 24 kHz rate.
  inline static constexpr const int SAMPLE_RATE = 24000;

  const std::string logFile{CTEST_RHVoiceController_DATA_DIR
                            "/CTEST_RHVoiceController.log"};
  const std::string wavFile{CTEST_RHVoiceController_DATA_DIR "/speech.wav"};

  RHVoiceController controller;
};

TEST_F(CTEST_RHVoiceController, english_speech_gets_into_the_wav_file)
{
  const auto speech = controller.synthesize("Hello, RHVoice!", "Alan");

  ASSERT_TRUE(speech.has_value());
  EXPECT_EQ(speech->get_sample_rate(), SAMPLE_RATE);
  EXPECT_GT(speech->get_duration().count(), 500);
  EXPECT_TRUE(sounds(speech->get_samples()));

  EXPECT_EQ(written_and_loaded(*speech), speech->get_samples());
}

TEST_F(CTEST_RHVoiceController, ukrainian_voices_speak_the_ukrainian_text)
{
  for (const auto* const voice : {"Anatol", "Natalia"}) {
    const auto speech = controller.synthesize("Привіт, світе!", voice);

    ASSERT_TRUE(speech.has_value()) << voice;
    EXPECT_EQ(speech->get_sample_rate(), SAMPLE_RATE) << voice;
    EXPECT_GT(speech->get_duration().count(), 500) << voice;
    EXPECT_TRUE(sounds(speech->get_samples())) << voice;
  }
}

TEST_F(CTEST_RHVoiceController, longer_text_gives_longer_speech)
{
  const auto shorter = controller.synthesize("One.", "Alan");
  const auto longer = controller.synthesize("One, two, three, four.", "Alan");

  ASSERT_TRUE(shorter.has_value());
  ASSERT_TRUE(longer.has_value());
  EXPECT_GT(longer->get_duration(), shorter->get_duration());
}

TEST_F(CTEST_RHVoiceController, unknown_voice_is_logged)
{
  EXPECT_FALSE(controller.synthesize("Hello", "nosuchvoice").has_value());

  EXPECT_THAT(log_contents(),
              HasSubstr("Fail to speak with the nosuchvoice RHVoice voice"));

  // The controller stays usable with a known voice.
  EXPECT_TRUE(controller.synthesize("Hello", "Alan").has_value());
}

TEST_F(CTEST_RHVoiceController, empty_text_gives_nothing)
{
  EXPECT_FALSE(controller.synthesize("", "Alan").has_value());
}

TEST_F(CTEST_RHVoiceController, speech_plays_through_the_dummy_driver)
{
  SDL_setenv("SDL_AUDIODRIVER", "dummy", 1);
  SDL_setenv("SDL_AUDIO_DRIVER", "dummy", 1);

  const auto speech = controller.synthesize("Hi!", "Alan");

  ASSERT_TRUE(speech.has_value());
  EXPECT_TRUE(tts::AudioPlayer{}.play(*speech, [] { return false; }));
}
