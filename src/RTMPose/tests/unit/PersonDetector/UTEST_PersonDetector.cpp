#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <opencv2/core.hpp>

#include "src/RTMPose/PersonDetector.h"

using namespace rtmpose;
using namespace testing;

TEST(UTEST_PersonDetector, decodes_the_persons_scored_above_the_least_score)
{
  const cv::Mat detections =
      (cv::Mat_<float>(3, 5) << 10.0F, 20.0F, 30.0F, 60.0F, 0.9F, 1.0F, 2.0F,
       3.0F, 4.0F, PersonDetector::MIN_SCORE, 40.0F, 0.0F, 100.0F, 50.0F,
       0.31F);

  const auto boxes = PersonDetector::decode(detections, 0.5F);

  ASSERT_EQ(boxes.size(), 2U);
  EXPECT_EQ(boxes[0], cv::Rect2f(20.0F, 40.0F, 40.0F, 80.0F));
  EXPECT_EQ(boxes[1], cv::Rect2f(80.0F, 0.0F, 120.0F, 100.0F));
}

TEST(UTEST_PersonDetector, nothing_is_detected_before_the_init)
{
  PersonDetector detector;

  EXPECT_FALSE(detector.init("no-such-model.onnx"));
  EXPECT_FALSE(detector.detect(cv::Mat(48, 64, CV_8UC3, cv::Scalar::all(9)))
                   .has_value());
}
