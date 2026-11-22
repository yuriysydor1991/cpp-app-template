#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <opencv2/core.hpp>
#include <string>

#include "src/OpenPose/OpenPoseController.h"

using namespace openpose;
using namespace testing;

/**
 * @brief Component test of the OpenPoseController running the real OpenCV
 * DNN module. The test cases which need the model of the PROJECT_POSE_MODEL
 * CMake variable directory skip themselves without it.
 */
class CTEST_OpenPoseController : public Test
{
 public:
  void load_the_model()
  {
    for (const auto* name :
         {OpenPoseController::NETWORK, OpenPoseController::WEIGHTS}) {
      if (!std::ifstream{std::filesystem::path{MODEL} / name}.good()) {
        GTEST_SKIP() << "No " << MODEL << " model is downloaded";
      }
    }

    ASSERT_TRUE(controller.init(MODEL));
  }

  inline static const std::string MODEL{CTEST_OpenPoseController_MODEL};

  OpenPoseController controller;
};

TEST_F(CTEST_OpenPoseController, missing_model_fails_to_init)
{
  EXPECT_FALSE(controller.init("no-such-model"));
}

TEST_F(CTEST_OpenPoseController, nothing_is_estimated_before_the_init)
{
  EXPECT_FALSE(controller.estimate(cv::Mat(48, 64, CV_8UC3, cv::Scalar::all(9)))
                   .has_value());
}

TEST_F(CTEST_OpenPoseController, blank_frame_shows_no_body)
{
  load_the_model();

  const auto poses =
      controller.estimate(cv::Mat(480, 640, CV_8UC3, cv::Scalar::all(127)));

  ASSERT_TRUE(poses.has_value());
  EXPECT_TRUE(poses->empty());
}

TEST_F(CTEST_OpenPoseController, gray_frame_fails)
{
  load_the_model();

  EXPECT_FALSE(controller.estimate(cv::Mat(48, 64, CV_8UC1, cv::Scalar::all(9)))
                   .has_value());
}
