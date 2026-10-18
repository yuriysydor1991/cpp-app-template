#include <SDL.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstddef>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include "src/TTS/WavWriter.h"

using namespace tts;
using namespace testing;

/**
 * @brief Unit test of the WavWriter, which reads the written files back with
 * the WAV loader of the SDL2 for an independent check of them.
 */
class UTEST_WavWriter : public Test
{
 public:
  /// @brief Reads the samples of the given WAV file and checks it's format.
  static Speech::samples load(const std::string& path, const int rate)
  {
    SDL_AudioSpec spec{};
    Uint8* wave{nullptr};
    Uint32 length{0U};

    if (SDL_LoadWAV(path.c_str(), &spec, &wave, &length) == nullptr) {
      ADD_FAILURE() << "The SDL fails to load the " << path
                    << " file: " << SDL_GetError();
      return {};
    }

    EXPECT_EQ(spec.freq, rate);
    EXPECT_EQ(spec.format, AUDIO_S16LSB);
    EXPECT_EQ(spec.channels, 1U);

    Speech::samples pcm(length / sizeof(Speech::sample));

    std::memcpy(pcm.data(), wave, pcm.size() * sizeof(Speech::sample));
    SDL_FreeWAV(wave);

    return pcm;
  }

  inline static constexpr const int SAMPLE_RATE = 22050;
  inline static constexpr const std::size_t HEADER_SIZE = 44U;

  const std::string path{UTEST_WavWriter_DATA_DIR "/speech.wav"};

  WavWriter writer;
};

TEST_F(UTEST_WavWriter, create_gives_an_instance)
{
  EXPECT_NE(WavWriter::create(), nullptr);
}

TEST_F(UTEST_WavWriter, writes_the_samples_and_the_format)
{
  const Speech::samples pcm{0, 1, -1, 1000, -1000, 32767, -32768};

  ASSERT_TRUE(writer.write(Speech{pcm, SAMPLE_RATE}, path));

  EXPECT_EQ(std::filesystem::file_size(path),
            HEADER_SIZE + pcm.size() * sizeof(Speech::sample));
  EXPECT_EQ(load(path, SAMPLE_RATE), pcm);
}

TEST_F(UTEST_WavWriter, writes_the_little_endian_header)
{
  ASSERT_TRUE(writer.write(Speech{{0x1234}, 16000}, path));

  std::ifstream file{path, std::ifstream::binary};
  const std::vector<unsigned char> bytes{std::istreambuf_iterator<char>{file},
                                         std::istreambuf_iterator<char>{}};

  const std::vector<unsigned char> expected{
      'R',  'I',  'F', 'F', 38U, 0U,   0U, 0U, 'W',  'A', 'V', 'E',
      'f',  'm',  't', ' ', 16U, 0U,   0U, 0U, 1U,   0U,  1U,  0U,
      0x80, 0x3E, 0U,  0U,  0U,  0x7D, 0U, 0U, 2U,   0U,  16U, 0U,
      'd',  'a',  't', 'a', 2U,  0U,   0U, 0U, 0x34, 0x12};

  EXPECT_EQ(bytes, expected);
}

TEST_F(UTEST_WavWriter, no_samples_give_an_empty_wav)
{
  ASSERT_TRUE(writer.write(Speech{{}, SAMPLE_RATE}, path));

  EXPECT_EQ(std::filesystem::file_size(path), HEADER_SIZE);
  EXPECT_TRUE(load(path, SAMPLE_RATE).empty());
}

TEST_F(UTEST_WavWriter, rewrites_the_previous_file)
{
  ASSERT_TRUE(writer.write(Speech{Speech::samples(100U), SAMPLE_RATE}, path));
  ASSERT_TRUE(writer.write(Speech{{7, 8}, SAMPLE_RATE}, path));

  EXPECT_EQ(load(path, SAMPLE_RATE), (Speech::samples{7, 8}));
}

TEST_F(UTEST_WavWriter, unwritable_path_fails)
{
  EXPECT_FALSE(writer.write(Speech{{1, 2, 3}, SAMPLE_RATE},
                            UTEST_WavWriter_DATA_DIR
                            "/no/such/dir/speech.wav"));
}
