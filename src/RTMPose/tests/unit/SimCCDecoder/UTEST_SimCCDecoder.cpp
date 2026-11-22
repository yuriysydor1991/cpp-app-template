#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <opencv2/core.hpp>
#include <tuple>
#include <vector>

#include "src/RTMPose/SimCCDecoder.h"

using namespace rtmpose;
using namespace testing;

class UTEST_SimCCDecoder : public Test
{
 public:
  /// @brief Gives the axis of the two keypoints responding at the bins.
  static cv::Mat axis(const int bins, const int first, const int second,
                      const float response)
  {
    cv::Mat values(2, bins, CV_32F, cv::Scalar::all(0.01F));

    values.at<float>(0, first) = response;
    values.at<float>(1, second) = response / 2.0F;

    return values;
  }
};

TEST_F(UTEST_SimCCDecoder, decodes_the_2d_keypoints)
{
  const auto pose = SimCCDecoder::decode(
      {axis(384, 100, 7, 0.8F), axis(512, 300, 511, 0.6F)});

  ASSERT_EQ(pose.size(), 2U);

  const auto& [first, firstScore] = pose[0];
  const auto& [second, secondScore] = pose[1];

  EXPECT_EQ(first, cv::Point3f(50.0F, 150.0F, 0.0F));
  EXPECT_FLOAT_EQ(firstScore, 0.6F);
  EXPECT_EQ(second, cv::Point3f(3.5F, 255.5F, 0.0F));
  EXPECT_FLOAT_EQ(secondScore, 0.3F);
}

TEST_F(UTEST_SimCCDecoder, decodes_the_depth_of_the_3d_keypoints)
{
  const auto pose =
      SimCCDecoder::decode({axis(576, 0, 0, 1.0F), axis(768, 0, 0, 1.0F),
                            axis(576, 288, 144, 1.0F)});

  ASSERT_EQ(pose.size(), 2U);
  EXPECT_FLOAT_EQ(std::get<0>(pose[0]).z, 0.0F);
  EXPECT_FLOAT_EQ(std::get<0>(pose[1]).z, -SimCCDecoder::Z_RANGE / 2.0F);
}
