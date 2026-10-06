#include <SDL.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

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

  /// @brief Picks the SDL audio driver of the microphone. The variables of
  /// the SDL3 run sdl2-compat library are given as well.
  static void use_audio_driver(const char* const driver,
                               const std::string& inputFile = {})
  {
    SDL_setenv("SDL_AUDIODRIVER", driver, 1);
    SDL_setenv("SDL_AUDIO_DRIVER", driver, 1);
    SDL_setenv("SDL_DISKAUDIOFILEIN", inputFile.c_str(), 1);
    SDL_setenv("SDL_AUDIO_DISK_INPUT_FILE", inputFile.c_str(), 1);
    SDL_setenv("SDL_DISKAUDIODELAY", "8", 1);
    SDL_setenv("SDL_AUDIO_DISK_TIMESCALE", "0.125", 1);
  }

  /// @brief Gives the little endian value of the given bytes count.
  static std::uint32_t little_endian(const std::vector<char>& bytes,
                                     const std::size_t offset,
                                     const std::size_t count)
  {
    std::uint32_t value = 0U;

    for (std::size_t index = count; index > 0U; --index) {
      value = (value << 8U) |
              static_cast<unsigned char>(bytes[offset + index - 1U]);
    }

    return value;
  }

  /// @brief Reads the 16 bit samples of the given WAVE file, whose RIFF
  /// chunks follow the 12 bytes of it's header.
  static samples read_wave(const char* const path)
  {
    std::ifstream file{path, std::ifstream::binary};
    const std::vector<char> bytes{std::istreambuf_iterator<char>{file}, {}};

    for (std::size_t chunk = 12U; chunk + 8U <= bytes.size();
         chunk += 8U + little_endian(bytes, chunk + 4U, 4U)) {
      if (std::string(bytes.data() + chunk, 4U) != "data") {
        continue;
      }

      // a truncated file carries less than the chunk header tells
      samples audio(std::min<std::size_t>(little_endian(bytes, chunk + 4U, 4U),
                                          bytes.size() - chunk - 8U) /
                    2U);

      for (std::size_t index = 0U; index < audio.size(); ++index) {
        audio[index] = static_cast<float>(static_cast<std::int16_t>(
                           little_endian(bytes, chunk + 8U + 2U * index, 2U))) /
                       32768.0F;
      }

      return audio;
    }

    return {};
  }

  /// @brief Makes the disk audio driver capture the speech sample.
  void speak_into_the_microphone() const
  {
    const auto audio = read_wave(SPEECH);

    std::ofstream{rawSpeech, std::ofstream::binary | std::ofstream::trunc}
        .write(reinterpret_cast<const char*>(audio.data()),
               static_cast<std::streamsize>(audio.size() * sizeof(float)));

    use_audio_driver("disk", rawSpeech);
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

  /// @brief Every test case gets the files of it's own, so the parallel ctest
  /// runs keep them apart.
  const std::string name{
      CTEST_WhisperController_DATA_DIR "/" +
      std::string{UnitTest::GetInstance()->current_test_info()->name()}};
  const std::string logFile{name + ".log"};
  const std::string rawSpeech{name + ".raw"};

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

  ASSERT_TRUE(controller->init(MODEL, "en"));

  EXPECT_THAT(controller->transcribe(read_wave(SPEECH)),
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
