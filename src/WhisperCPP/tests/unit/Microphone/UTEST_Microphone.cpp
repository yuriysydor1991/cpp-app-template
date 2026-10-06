#include <SDL.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <cstddef>
#include <fstream>
#include <string>
#include <thread>

#include "src/WhisperCPP/Microphone.h"

using namespace whisperi;
using namespace testing;

/**
 * @brief Unit test of the Microphone over the demand only SDL audio drivers,
 * so no real device takes part: the dummy one captures the silence, while the
 * disk one captures the contents of a file the test writes.
 */
class UTEST_Microphone : public Test
{
 public:
  using samples = Microphone::samples;

  /// @brief Picks the SDL audio driver of the microphone. The variables of
  /// the SDL3 run sdl2-compat library are given as well.
  static void use_audio_driver(const char* const driver,
                               const std::string& inputFile = {})
  {
    SDL_setenv("SDL_AUDIODRIVER", driver, 1);
    SDL_setenv("SDL_AUDIO_DRIVER", driver, 1);
    SDL_setenv("SDL_DISKAUDIOFILEIN", inputFile.c_str(), 1);
    SDL_setenv("SDL_AUDIO_DISK_INPUT_FILE", inputFile.c_str(), 1);
  }

  /// @brief Reads the microphone till the given samples count is captured or
  /// a couple of seconds pass.
  samples read_at_least(const std::size_t count)
  {
    samples captured;

    for (int attempt = 0; captured.size() < count && attempt < 200; ++attempt) {
      std::this_thread::sleep_for(std::chrono::milliseconds{10});

      const auto next = microphone.read();

      captured.insert(captured.end(), next.cbegin(), next.cend());
    }

    return captured;
  }

  inline static constexpr const int SAMPLE_RATE = 16000;
  inline static constexpr const std::size_t TENTH = SAMPLE_RATE / 10;

  Microphone microphone;
};

TEST_F(UTEST_Microphone, create_gives_an_instance)
{
  EXPECT_NE(Microphone::create(), nullptr);
}

TEST_F(UTEST_Microphone, read_before_open_gives_nothing)
{
  EXPECT_TRUE(microphone.read().empty());
}

TEST_F(UTEST_Microphone, the_dummy_driver_captures_the_silence)
{
  use_audio_driver("dummy");

  ASSERT_TRUE(microphone.open(SAMPLE_RATE));

  const auto captured = read_at_least(TENTH);

  EXPECT_GE(captured.size(), TENTH);
  EXPECT_THAT(captured, Each(0.0F));
}

TEST_F(UTEST_Microphone, the_disk_driver_captures_the_file)
{
  const std::string path{UTEST_Microphone_DATA_DIR "/ramp.raw"};

  samples ramp(TENTH);

  for (std::size_t index = 0U; index < ramp.size(); ++index) {
    ramp[index] = static_cast<float>(index) / static_cast<float>(TENTH);
  }

  std::ofstream{path, std::ofstream::binary | std::ofstream::trunc}.write(
      reinterpret_cast<const char*>(ramp.data()),
      static_cast<std::streamsize>(ramp.size() * sizeof(float)));

  use_audio_driver("disk", path);

  ASSERT_TRUE(microphone.open(SAMPLE_RATE));

  const auto captured = read_at_least(ramp.size());

  ASSERT_GE(captured.size(), ramp.size());
  EXPECT_EQ(samples(captured.cbegin(),
                    captured.cbegin() + static_cast<std::ptrdiff_t>(TENTH)),
            ramp);
}

TEST_F(UTEST_Microphone, open_after_a_successful_one_does_nothing)
{
  use_audio_driver("dummy");

  ASSERT_TRUE(microphone.open(SAMPLE_RATE));
  EXPECT_TRUE(microphone.open(SAMPLE_RATE));
  EXPECT_FALSE(read_at_least(TENTH).empty());
}

TEST_F(UTEST_Microphone, an_unknown_driver_fails_the_open)
{
  use_audio_driver("nosuchdriver");

  EXPECT_FALSE(microphone.open(SAMPLE_RATE));
  EXPECT_TRUE(microphone.read().empty());
}
