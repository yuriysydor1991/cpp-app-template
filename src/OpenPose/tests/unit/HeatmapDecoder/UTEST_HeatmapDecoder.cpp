#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <opencv2/core.hpp>

#include "src/OpenPose/HeatmapDecoder.h"

using namespace openpose;
using namespace testing;

class UTEST_HeatmapDecoder : public Test
{
 public:
  static constexpr const int CHANNELS = 57;

  const int dimensions[4] = {1, CHANNELS, 46, 46};
  cv::Mat output{4, dimensions, CV_32F, cv::Scalar::all(0.0F)};
};

TEST_F(UTEST_HeatmapDecoder, weak_heatmaps_show_no_body)
{
  output.ptr<float>(0, 3)[100] = HeatmapDecoder::MIN_SCORE / 2.0F;

  EXPECT_TRUE(HeatmapDecoder::decode(output, {368.0F, 368.0F}).empty());
}

TEST_F(UTEST_HeatmapDecoder, decodes_the_peaks_of_the_keypoint_heatmaps)
{
  output.ptr<float>(0, 0)[2 * 46 + 5] = 0.7F;
  output.ptr<float>(0, 17)[45 * 46 + 45] = 0.2F;
  output.ptr<float>(0, 18)[46] = 0.9F;

  const auto poses = HeatmapDecoder::decode(output, {92.0F, 184.0F});

  ASSERT_EQ(poses.size(), 1U);
  ASSERT_EQ(poses.front().size(), HeatmapDecoder::KEYPOINTS);

  const auto& [nose, noseScore] = poses.front().front();
  const auto& [ear, earScore] = poses.front().back();

  EXPECT_EQ(nose, cv::Point3f(10.0F, 8.0F, 0.0F));
  EXPECT_FLOAT_EQ(noseScore, 0.7F);
  EXPECT_EQ(ear, cv::Point3f(90.0F, 180.0F, 0.0F));
  EXPECT_FLOAT_EQ(earScore, 0.2F);
}
