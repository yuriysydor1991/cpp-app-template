#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>

#include "src/TTS/Speech.h"

using namespace tts;
using namespace testing;

class UTEST_Speech : public Test
{
 public:
  inline static constexpr const int SAMPLE_RATE = 22050;
};

TEST_F(UTEST_Speech, keeps_the_samples_and_the_rate)
{
  const Speech::samples pcm{0, 1, -1, 32767, -32768};

  const Speech speech{pcm, SAMPLE_RATE};

  EXPECT_EQ(speech.get_samples(), pcm);
  EXPECT_EQ(speech.get_sample_rate(), SAMPLE_RATE);
}

TEST_F(UTEST_Speech, duration_follows_the_samples_count)
{
  const Speech speech{Speech::samples(SAMPLE_RATE * 3 / 2), SAMPLE_RATE};

  EXPECT_EQ(speech.get_duration(), std::chrono::milliseconds{1500});
}

TEST_F(UTEST_Speech, no_samples_last_nothing)
{
  const Speech speech{{}, SAMPLE_RATE};

  EXPECT_TRUE(speech.get_samples().empty());
  EXPECT_EQ(speech.get_duration(), std::chrono::milliseconds{0});
}

TEST_F(UTEST_Speech, no_valid_rate_lasts_nothing)
{
  EXPECT_EQ(Speech(Speech::samples(SAMPLE_RATE), 0).get_duration(),
            std::chrono::milliseconds{0});
  EXPECT_EQ(Speech(Speech::samples(SAMPLE_RATE), -1).get_duration(),
            std::chrono::milliseconds{0});
}
