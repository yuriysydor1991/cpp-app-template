#include <SDL.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <whisper.h>

#include <cstddef>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

#include "src/WhisperCPP/WhisperController.h"
#include "src/log/log.h"
#include "src/log/severity-macro-consts.h"

using namespace whisperi;
using namespace testing;

/**
 * @brief Component test of the WhisperController driving the real whisper.cpp
 * and SDL2 libraries.
 *
 * The microphone is the demand only disk audio driver of the SDL, which
 * captures the speech sample of the whisper.cpp sources 8 times faster than
 * the real time, or the dummy one, which captures the silence. The empty model
 * of the whisper.cpp tests, the one holding no weights, proves the whole chain
 * but the recognition itself, which the model of the PROJECT_WHISPER_MODEL_PATH
 * CMake variable proves once downloaded. The test cases skip themselves while
 * the files they need are not available.
 */
class CTEST_WhisperController : public Test
{
 public:
  using samples = WhisperController::samples;

  CTEST_WhisperController()
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

  static bool available(const char* const path)
  {
    return std::ifstream{path}.good();
  }

  /// @brief Picks the SDL audio driver of the microphone. The variable of the
  /// SDL3 run sdl2-compat library is given as well.
  static void use_audio_driver(const char* const driver)
  {
    SDL_setenv("SDL_AUDIODRIVER", driver, 1);
    SDL_setenv("SDL_AUDIO_DRIVER", driver, 1);
  }

  /// @brief Reads the given WAVE file into the mono samples of the given
  /// rate.
  static samples read_wave(const char* const path, const int rate)
  {
    SDL_AudioSpec spec{};
    Uint8* wave{nullptr};
    Uint32 length{0U};

    if (SDL_LoadWAV(path, &spec, &wave, &length) == nullptr) {
      return {};
    }

    SDL_AudioStream* const stream = SDL_NewAudioStream(
        spec.format, spec.channels, spec.freq, AUDIO_F32SYS, 1U, rate);

    SDL_AudioStreamPut(stream, wave, static_cast<int>(length));
    SDL_AudioStreamFlush(stream);
    SDL_FreeWAV(wave);

    samples audio(static_cast<std::size_t>(SDL_AudioStreamAvailable(stream)) /
                  sizeof(float));

    SDL_AudioStreamGet(stream, audio.data(),
                       static_cast<int>(audio.size() * sizeof(float)));
    SDL_FreeAudioStream(stream);

    return audio;
  }

  /// @brief Makes the disk audio driver capture the speech sample. The SDL2
  /// reads the file at the rate the microphone asks for, while the SDL3 gets
  /// the file of it's own at the SDL3_RATE.
  void speak_into_the_microphone() const
  {
    for (const auto& [file, rate] : {std::pair{rawSpeech, WHISPER_SAMPLE_RATE},
                                     std::pair{sdl3RawSpeech, SDL3_RATE}}) {
      const auto audio = read_wave(SPEECH, rate);

      std::ofstream{file, std::ofstream::binary | std::ofstream::trunc}.write(
          reinterpret_cast<const char*>(audio.data()),
          static_cast<std::streamsize>(audio.size() * sizeof(float)));
    }

    use_audio_driver("disk");

    SDL_setenv("SDL_DISKAUDIOFILEIN", rawSpeech.c_str(), 1);
    SDL_setenv("SDL_AUDIO_DISK_INPUT_FILE", sdl3RawSpeech.c_str(), 1);
    SDL_setenv("SDL_DISKAUDIODELAY", "8", 1);
    SDL_setenv("SDL_AUDIO_DISK_TIMESCALE", "0.125", 1);
  }

  /// @brief Listens to the microphone till the heard text carries the given
  /// one or the given count of the WhisperController::listen calls pass.
  std::string listen_for(const std::string& text, const int calls) const
  {
    std::string heard;

    for (int call = 0; call < calls && heard.find(text) == std::string::npos;
         ++call) {
      const auto next = controller->listen();

      if (!next.has_value()) {
        break;
      }

      heard += *next;
    }

    return heard;
  }

  inline static constexpr const char* const TEST_MODEL =
      CTEST_WhisperController_TEST_MODEL;
  inline static constexpr const char* const MODEL =
      CTEST_WhisperController_MODEL;
  inline static constexpr const char* const SPEECH =
      CTEST_WhisperController_SPEECH;
  inline static constexpr const char* const PHRASE =
      "ask not what your country can do for you";

  /// @brief The SDL3 behind the sdl2-compat runs the recording devices at
  /// this rate at least, so it's disk driver reads the file at it and converts
  /// the audio into the WHISPER_SAMPLE_RATE the microphone asks for.
  inline static constexpr const int SDL3_RATE = 44100;

  /// @brief Every test case gets the files of it's own, so the parallel ctest
  /// runs keep them apart.
  const std::string name{
      CTEST_WhisperController_DATA_DIR "/" +
      std::string{UnitTest::GetInstance()->current_test_info()->name()}};
  const std::string logFile{name + ".log"};
  const std::string rawSpeech{name + ".raw"};
  const std::string sdl3RawSpeech{name + ".sdl3.raw"};

  WhisperControllerPtr controller{WhisperController::create()};
};

TEST_F(CTEST_WhisperController, an_absent_model_fails_the_init)
{
  EXPECT_FALSE(controller->init("an-absent-model.bin", "auto"));
  EXPECT_FALSE(controller->transcribe(samples(16000U, 0.0F)).has_value());
}

TEST_F(CTEST_WhisperController, the_whisper_messages_get_into_the_project_log)
{
  if (!available(TEST_MODEL)) {
    GTEST_SKIP() << "No " << TEST_MODEL << " test model downloaded";
  }

  ASSERT_TRUE(controller->init(TEST_MODEL, "auto"));

  EXPECT_THAT(log_contents(), HasSubstr("whisper_model_load"));
}

TEST_F(CTEST_WhisperController, an_absent_microphone_fails_the_listening)
{
  if (!available(TEST_MODEL)) {
    GTEST_SKIP() << "No " << TEST_MODEL << " test model downloaded";
  }

  use_audio_driver("nosuchdriver");

  ASSERT_TRUE(controller->init(TEST_MODEL, "auto"));

  EXPECT_FALSE(controller->listen().has_value());
}

TEST_F(CTEST_WhisperController, the_silence_gets_no_transcription)
{
  if (!available(TEST_MODEL)) {
    GTEST_SKIP() << "No " << TEST_MODEL << " test model downloaded";
  }

  use_audio_driver("dummy");

  ASSERT_TRUE(controller->init(TEST_MODEL, "auto"));

  EXPECT_EQ(listen_for(PHRASE, 20), "");
  EXPECT_THAT(log_contents(), Not(HasSubstr("Transcribing the")));
}

TEST_F(CTEST_WhisperController, the_heard_speech_gets_transcribed)
{
  if (!available(TEST_MODEL) || !available(SPEECH)) {
    GTEST_SKIP() << "No " << TEST_MODEL << " or " << SPEECH << " downloaded";
  }

  speak_into_the_microphone();

  ASSERT_TRUE(controller->init(TEST_MODEL, "en"));

  // the empty model recognizes no text, so the listening goes on till the
  // last of the calls
  EXPECT_EQ(listen_for(PHRASE, 50), "");
  EXPECT_THAT(log_contents(), HasSubstr("Transcribing the"));
}

TEST_F(CTEST_WhisperController, the_speech_sample_gets_recognized)
{
  if (!available(MODEL) || !available(SPEECH)) {
    GTEST_SKIP() << "No " << MODEL << " or " << SPEECH
                 << " downloaded, configure with the "
                    "-DENABLE_WHISPERCPP_MODEL_DOWNLOAD=ON for the model";
  }

  // a multilingual model detects the English of the sample on it's own
  ASSERT_TRUE(controller->init(MODEL, "auto"));

  EXPECT_THAT(controller->transcribe(read_wave(SPEECH, WHISPER_SAMPLE_RATE)),
              Optional(HasSubstr(PHRASE)));
}

TEST_F(CTEST_WhisperController, the_heard_speech_gets_recognized)
{
  if (!available(MODEL) || !available(SPEECH)) {
    GTEST_SKIP() << "No " << MODEL << " or " << SPEECH
                 << " downloaded, configure with the "
                    "-DENABLE_WHISPERCPP_MODEL_DOWNLOAD=ON for the model";
  }

  speak_into_the_microphone();

  ASSERT_TRUE(controller->init(MODEL, "en"));

  EXPECT_THAT(listen_for("country", 100), HasSubstr("country"));
}
