#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <opencv2/core.hpp>
#include <tuple>

#include "src/MoveNet/MoveNetDecoder.h"

using namespace movenet;
using namespace testing;

class UTEST_MoveNetDecoder : public Test
{
 public:
  static constexpr const std::size_t VALUES =
      MoveNetDecoder::BODIES * MoveNetDecoder::BODY_VALUES;

  /// @brief Gives the body the given score with every keypoint at (y, x).
  void body(const std::size_t index, const float score, const float y,
            const float x)
  {
    float* values = output.data() + (index * MoveNetDecoder::BODY_VALUES);

    for (std::size_t point = 0; point < MoveNetDecoder::KEYPOINTS; ++point) {
      float* keypoint = values + (point * MoveNetDecoder::KEYPOINT_VALUES);

      keypoint[0] = y;
      keypoint[1] = x;
      keypoint[2] = 0.9F;
    }

    values[MoveNetDecoder::BODY_VALUES - 1U] = score;
  }

  std::array<float, VALUES> output{};
};

TEST_F(UTEST_MoveNetDecoder, no_scored_body_gives_no_pose)
{
  EXPECT_TRUE(MoveNetDecoder::decode(output.data(), {100.0F, 50.0F}).empty());
}

TEST_F(UTEST_MoveNetDecoder, bodies_below_the_least_score_are_dropped)
{
  body(1U, MoveNetDecoder::MIN_BODY_SCORE - 0.01F, 0.5F, 0.5F);
  body(4U, MoveNetDecoder::MIN_BODY_SCORE, 0.25F, 0.5F);

  const auto poses = MoveNetDecoder::decode(output.data(), {100.0F, 50.0F});

  ASSERT_EQ(poses.size(), 1U);
  ASSERT_EQ(poses.front().size(), MoveNetDecoder::KEYPOINTS);

  for (const auto& [position, score] : poses.front()) {
    EXPECT_FLOAT_EQ(position.x, 50.0F);
    EXPECT_FLOAT_EQ(position.y, 12.5F);
    EXPECT_FLOAT_EQ(position.z, 0.0F);
    EXPECT_FLOAT_EQ(score, 0.9F);
  }
}
