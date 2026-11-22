#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <opencv2/core.hpp>

#include "src/RTMPose/PoseCrop.h"

using namespace rtmpose;
using namespace testing;

TEST(UTEST_PoseCrop, maps_the_box_center_to_the_input_center)
{
  const PoseCrop crop{{100.0F, 50.0F, 40.0F, 80.0F}, {192, 256}};
  const cv::Point2f center = crop.to_frame({96.0F, 128.0F});

  EXPECT_FLOAT_EQ(center.x, 120.0F);
  EXPECT_FLOAT_EQ(center.y, 90.0F);
}

TEST(UTEST_PoseCrop, pads_the_box_and_keeps_the_input_aspect_ratio)
{
  // The 40x80 box padded to 50x100 is narrower than the 3:4 input, so it is
  // widened to 75x100: the input spans the 100 frame pixels vertically.
  const PoseCrop crop{{100.0F, 50.0F, 40.0F, 80.0F}, {192, 256}};
  const cv::Point2f top = crop.to_frame({96.0F, 0.0F});
  const cv::Point2f left = crop.to_frame({0.0F, 128.0F});

  EXPECT_FLOAT_EQ(top.y, 40.0F);
  EXPECT_FLOAT_EQ(left.x, 82.5F);
}

TEST(UTEST_PoseCrop, warps_the_box_into_the_input)
{
  cv::Mat frame(200, 300, CV_8UC3, cv::Scalar::all(0));

  frame(cv::Rect{110, 60, 20, 60}).setTo(cv::Scalar::all(255));

  const PoseCrop crop{{110.0F, 60.0F, 20.0F, 60.0F}, {192, 256}};
  const cv::Mat input = crop.warp(frame);

  ASSERT_EQ(input.size(), cv::Size(192, 256));
  EXPECT_EQ(input.at<cv::Vec3b>(128, 96), cv::Vec3b(255, 255, 255));
  EXPECT_EQ(input.at<cv::Vec3b>(128, 5), cv::Vec3b(0, 0, 0));
}
