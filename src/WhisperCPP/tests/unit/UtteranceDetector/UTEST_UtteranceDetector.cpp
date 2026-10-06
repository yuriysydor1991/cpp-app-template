#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <vector>

#include "src/WhisperCPP/UtteranceDetector.h"

using namespace whisperi;
using namespace testing;

/**
 * @brief Unit test of the UtteranceDetector. A steady tone stands for the
 * speech, since the detector tells the speech by it's loudness alone.
 */
class UTEST_UtteranceDetector : public Test
{
 public:
  using samples = UtteranceDetector::samples;

  static std::size_t samples_of(const std::size_t milliseconds)
  {
    return SAMPLE_RATE * milliseconds / 1000U;
  }

  static samples silence(const std::size_t milliseconds)
  {
    return samples(samples_of(milliseconds), 0.0F);
  }

  /// @brief The 440 Hz tone of the AMPLITUDE amplitude.
  static samples tone(const std::size_t milliseconds)
  {
    static constexpr const float step =
        2.0F * 3.14159265F * 440.0F / static_cast<float>(SAMPLE_RATE);

    samples audio(samples_of(milliseconds));

    for (std::size_t index = 0U; index < audio.size(); ++index) {
      audio[index] = AMPLITUDE * std::sin(step * static_cast<float>(index));
    }

    return audio;
  }

  /// @brief The steady pseudo random noise of the NOISE_AMPLITUDE amplitude.
  static samples noise(const std::size_t milliseconds)
  {
    std::uint32_t state = 1U;
    samples audio(samples_of(milliseconds));

    for (auto& sample : audio) {
      state = state * 1664525U + 1013904223U;
      sample = NOISE_AMPLITUDE *
               (static_cast<float>(state) / 4294967295.0F * 2.0F - 1.0F);
    }

    return audio;
  }

  static samples join(const std::initializer_list<samples> parts)
  {
    samples joined;

    for (const auto& part : parts) {
      joined.insert(joined.end(), part.cbegin(), part.cend());
    }

    return joined;
  }

  /// @brief A second of the speech surrounded by the seconds of the silence.
  static samples speech()
  {
    return join({silence(1000U), tone(1000U), silence(1000U)});
  }

  inline static constexpr const std::size_t SAMPLE_RATE = 16000U;
  inline static constexpr const float AMPLITUDE = 0.1F;
  inline static constexpr const float NOISE_AMPLITUDE = 0.02F;

  UtteranceDetector detector{SAMPLE_RATE};
};

TEST_F(UTEST_UtteranceDetector, silence_completes_no_utterance)
{
  EXPECT_TRUE(detector.feed(silence(10000U)).empty());
}

TEST_F(UTEST_UtteranceDetector, a_steady_noise_completes_no_utterance)
{
  EXPECT_TRUE(detector.feed(noise(10000U)).empty());
}

TEST_F(UTEST_UtteranceDetector, a_pause_completes_the_utterance)
{
  const auto utterance = detector.feed(speech());

  // the lead, the speech and the pause it ends with, give or take a frame
  // the speech starts and ends inside of
  EXPECT_NEAR(static_cast<double>(utterance.size()),
              static_cast<double>(samples_of(300U + 1000U + 750U)),
              static_cast<double>(samples_of(60U)));
}

TEST_F(UTEST_UtteranceDetector, the_utterance_starts_with_the_lead)
{
  const auto utterance = detector.feed(speech());

  ASSERT_GT(utterance.size(), samples_of(300U));

  const auto leadEnd =
      utterance.cbegin() + static_cast<std::ptrdiff_t>(samples_of(300U));

  EXPECT_TRUE(std::all_of(utterance.cbegin(), leadEnd,
                          [](const float sample) { return sample == 0.0F; }));
  EXPECT_NEAR(static_cast<double>(*std::max_element(leadEnd, utterance.cend())),
              static_cast<double>(AMPLITUDE), 0.001);
}

TEST_F(UTEST_UtteranceDetector,
       a_speech_over_a_steady_noise_completes_the_utterance)
{
  EXPECT_FALSE(
      detector.feed(join({noise(1000U), tone(1000U), noise(1000U)})).empty());
}

TEST_F(UTEST_UtteranceDetector, a_click_completes_no_utterance)
{
  EXPECT_TRUE(detector.feed(join({silence(1000U), tone(100U), silence(2000U)}))
                  .empty());
}

TEST_F(UTEST_UtteranceDetector, a_speech_of_no_pause_gets_cut_at_the_maximum)
{
  EXPECT_EQ(detector.feed(join({silence(1000U), tone(20000U)})).size(),
            samples_of(15000U));
}

TEST_F(UTEST_UtteranceDetector,
       the_audio_behind_the_utterance_awaits_the_next_feed)
{
  EXPECT_FALSE(detector.feed(join({speech(), speech()})).empty());
  EXPECT_FALSE(detector.feed({}).empty());
  EXPECT_TRUE(detector.feed({}).empty());
}

TEST_F(UTEST_UtteranceDetector, the_feeding_pieces_change_no_utterance)
{
  static constexpr const std::size_t piece = 100U;

  const auto audio = speech();
  const auto whole = UtteranceDetector{SAMPLE_RATE}.feed(audio);

  samples pieces;

  for (std::size_t offset = 0U; pieces.empty() && offset < audio.size();
       offset += piece) {
    const auto begin = audio.cbegin() + static_cast<std::ptrdiff_t>(offset);

    pieces = detector.feed({begin, begin + static_cast<std::ptrdiff_t>(std::min(
                                               piece, audio.size() - offset))});
  }

  ASSERT_FALSE(whole.empty());
  EXPECT_EQ(pieces, whole);
}
