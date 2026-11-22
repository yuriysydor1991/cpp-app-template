#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>
#include <opencv2/core.hpp>
#include <string>

#include "src/MoveNet/MoveNetController.h"

using namespace movenet;
using namespace testing;

/**
 * @brief Component test of the MoveNetController running the real ONNX
 * Runtime. The test cases which need the model of the PROJECT_POSE_MODEL
 * CMake variable skip themselves without it.
 */
class CTEST_MoveNetController : public Test
{
 public:
  void load_the_model()
  {
    if (!std::ifstream{MODEL}.good()) {
      GTEST_SKIP() << "No " << MODEL << " model is downloaded";
    }

    ASSERT_TRUE(controller.init(MODEL));
  }

  inline static const std::string MODEL{CTEST_MoveNetController_MODEL};

  MoveNetController controller;
};

TEST_F(CTEST_MoveNetController, missing_model_fails_to_init)
{
  EXPECT_FALSE(controller.init("no-such-model.onnx"));
}

TEST_F(CTEST_MoveNetController, nothing_is_estimated_before_the_init)
{
  EXPECT_FALSE(controller.estimate(cv::Mat(48, 64, CV_8UC3, cv::Scalar::all(9)))
                   .has_value());
}

TEST_F(CTEST_MoveNetController, blank_frames_show_no_body)
{
  load_the_model();

  for (const cv::Size size : {cv::Size{640, 480}, cv::Size{120, 360}}) {
    const auto poses =
        controller.estimate(cv::Mat(size, CV_8UC3, cv::Scalar::all(127)));

    ASSERT_TRUE(poses.has_value());
    EXPECT_TRUE(poses->empty());
  }
}

TEST_F(CTEST_MoveNetController, gray_frame_fails)
{
  load_the_model();

  EXPECT_FALSE(controller.estimate(cv::Mat(48, 64, CV_8UC1, cv::Scalar::all(9)))
                   .has_value());
}
