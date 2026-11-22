#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <array>
#include <opencv2/core.hpp>

#include "src/MediaPipe/LandmarksDecoder.h"

using namespace mediapipei;
using namespace testing;

TEST(UTEST_LandmarksDecoder, no_body_gives_no_pose)
{
  EXPECT_TRUE(LandmarksDecoder::decode({}, {640.0F, 480.0F}).empty());
}

TEST(UTEST_LandmarksDecoder, decodes_the_landmarks_into_the_frame_pixels)
{
  std::array<MpNormalizedLandmark, 2> marks{};

  marks[0] = {0.5F, 0.25F, -0.1F, true, 0.9F, false, 0.0F, nullptr};
  marks[1] = {1.0F, 1.0F, 0.0F, false, 0.0F, false, 0.0F, nullptr};

  MpNormalizedLandmarks body{marks.data(), 2U};
  MpPoseLandmarkerResult result{};

  result.pose_landmarks = &body;
  result.pose_landmarks_count = 1U;

  const auto poses = LandmarksDecoder::decode(result, {640.0F, 480.0F});

  ASSERT_EQ(poses.size(), 1U);
  ASSERT_EQ(poses.front().size(), 2U);

  const auto& [first, firstScore] = poses.front()[0];
  const auto& [second, secondScore] = poses.front()[1];

  EXPECT_EQ(first, cv::Point3f(320.0F, 120.0F, -64.0F));
  EXPECT_FLOAT_EQ(firstScore, 0.9F);
  EXPECT_EQ(second, cv::Point3f(640.0F, 480.0F, 0.0F));
  EXPECT_FLOAT_EQ(secondScore, 1.0F);
}
