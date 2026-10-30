#include <SDL.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstddef>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

#include "src/STT/ISpeechRecognizer.h"
#include "src/STT/Microphone.h"
#include "src/STT/SpeechListener.h"
#include "src/SherpaONNX/SherpaONNXController.h"
#include "src/log/log.h"
#include "src/log/severity-macro-consts.h"

using namespace sherpaonnx;
using namespace testing;

/**
 * @brief Component test of the SherpaONNXController driving the real
 * sherpa-onnx and SDL2 libraries.
 *
 * The model of the PROJECT_STT_MODEL CMake variable recognizes the English
 * speech sample it comes with and the Ukrainian one of the sherpa-onnx
 * asr-models release. The microphone of the SpeechListener is the demand only
 * disk audio driver of the SDL, which captures the English sample 8 times
 * faster than the real time, or the dummy one, which captures the silence.
 * The test cases skip themselves while the files they need are not available.
 */
class CTEST_SherpaONNXController : public Test
{
 public:
  using samples = stt::ISpeechRecognizer::samples;

  CTEST_SherpaONNXController()
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

  static bool available(const std::string& path)
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
  static samples read_wave(const std::string& path, const int rate)
  {
    SDL_AudioSpec spec{};
    Uint8* wave{nullptr};
    Uint32 length{0U};

    if (SDL_LoadWAV(path.c_str(), &spec, &wave, &length) == nullptr) {
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

  /// @brief Makes the disk audio driver capture the English speech sample.
  /// The SDL2 reads the file at the rate the microphone asks for, while the
  /// SDL3 gets the file of it's own at the SDL3_RATE.
  void speak_into_the_microphone() const
  {
    for (const auto& [file, rate] :
         {std::pair{rawSpeech, RATE}, std::pair{sdl3RawSpeech, SDL3_RATE}}) {
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
  /// one or the given count of the SpeechListener::listen calls pass.
  std::string listen_for(const std::string& text, const int calls)
  {
    std::string heard;

    for (int call = 0; call < calls && heard.find(text) == std::string::npos;
         ++call) {
      const auto next = listener.listen();

      if (!next.has_value()) {
        break;
      }

      heard += *next;
    }

    return heard;
  }

  inline static const std::string MODEL{CTEST_SherpaONNXController_MODEL};
  inline static const std::string SPEECH{CTEST_SherpaONNXController_SPEECH};
  inline static const std::string UK_SPEECH{
      CTEST_SherpaONNXController_UK_SPEECH};
  inline static constexpr const int RATE = stt::ISpeechRecognizer::SAMPLE_RATE;

  /// @brief The SDL3 behind the sdl2-compat runs the recording devices at
  /// this rate at least, so it's disk driver reads the file at it and converts
  /// the audio into the RATE the microphone asks for.
  inline static constexpr const int SDL3_RATE = 44100;

  /// @brief Every test case gets the files of it's own, so the parallel ctest
  /// runs keep them apart.
  const std::string name{
      CTEST_SherpaONNXController_DATA_DIR "/" +
      std::string{UnitTest::GetInstance()->current_test_info()->name()}};
  const std::string logFile{name + ".log"};
  const std::string rawSpeech{name + ".raw"};
  const std::string sdl3RawSpeech{name + ".sdl3.raw"};

  const std::shared_ptr<SherpaONNXController> controller{
      std::make_shared<SherpaONNXController>()};

  stt::SpeechListener listener{controller, stt::Microphone::create()};
};

TEST_F(CTEST_SherpaONNXController, an_absent_model_fails_the_init)
{
  EXPECT_FALSE(controller->init("an-absent-model"));
  EXPECT_FALSE(controller->recognize(samples(RATE, 0.0F)).has_value());
  EXPECT_THAT(log_contents(), HasSubstr("Fail to load the sherpa-onnx"));
}

TEST_F(CTEST_SherpaONNXController, the_english_sample_gets_recognized)
{
  if (!available(SPEECH)) {
    GTEST_SKIP() << "No " << SPEECH
                 << " downloaded, configure with the "
                    "-DENABLE_SHERPA_ONNX_MODEL_DOWNLOAD=ON for the model";
  }

  ASSERT_TRUE(controller->init(MODEL));

  EXPECT_THAT(controller->recognize(read_wave(SPEECH, RATE)),
              Optional(HasSubstr("what your country can do for you")));
  EXPECT_THAT(log_contents(), HasSubstr("directory is loaded"));
}

TEST_F(CTEST_SherpaONNXController, the_ukrainian_sample_gets_recognized)
{
  if (!available(MODEL + "/tokens.txt") || !available(UK_SPEECH)) {
    GTEST_SKIP() << "No " << MODEL << " or " << UK_SPEECH << " downloaded";
  }

  ASSERT_TRUE(controller->init(MODEL));

  EXPECT_THAT(controller->recognize(read_wave(UK_SPEECH, RATE)),
              Optional(HasSubstr("що ти можеш зробити для своєї країни")));
}

TEST_F(CTEST_SherpaONNXController, an_absent_microphone_fails_the_listening)
{
  if (!available(MODEL + "/tokens.txt")) {
    GTEST_SKIP() << "No " << MODEL << " downloaded";
  }

  use_audio_driver("nosuchdriver");

  ASSERT_TRUE(listener.init(MODEL));

  EXPECT_FALSE(listener.listen().has_value());
}

TEST_F(CTEST_SherpaONNXController, the_silence_gets_no_recognition)
{
  if (!available(MODEL + "/tokens.txt")) {
    GTEST_SKIP() << "No " << MODEL << " downloaded";
  }

  use_audio_driver("dummy");

  ASSERT_TRUE(listener.init(MODEL));

  EXPECT_EQ(listen_for("country", 20), "");
  EXPECT_THAT(log_contents(), Not(HasSubstr("Recognizing the")));
}

TEST_F(CTEST_SherpaONNXController, the_heard_speech_gets_recognized)
{
  if (!available(SPEECH)) {
    GTEST_SKIP() << "No " << SPEECH << " downloaded";
  }

  speak_into_the_microphone();

  ASSERT_TRUE(listener.init(MODEL));

  EXPECT_THAT(listen_for("country", 100), HasSubstr("country"));
  EXPECT_THAT(log_contents(), HasSubstr("Recognizing the"));
}
