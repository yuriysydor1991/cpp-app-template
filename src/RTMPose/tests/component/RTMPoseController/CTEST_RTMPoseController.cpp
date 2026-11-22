#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cmath>
#include <filesystem>
#include <fstream>
#include <opencv2/core.hpp>
#include <string>

#include "src/RTMPose/PoseModel.h"
#include "src/RTMPose/RTMPoseController.h"

using namespace rtmpose;
using namespace testing;

/**
 * @brief Component test of the RTMPoseController running the real ONNX
 * Runtime. The test cases which need the models of the PROJECT_POSE_MODEL
 * CMake variable directory skip themselves without them.
 */
class CTEST_RTMPoseController : public Test
{
 public:
  static std::string model(const char* const name)
  {
    return (std::filesystem::path{MODEL} / name).string();
  }

  static void skip_without_the_models()
  {
    for (const auto* name :
         {RTMPoseController::DETECTOR, RTMPoseController::POSE}) {
      if (!std::ifstream{model(name)}.good()) {
        GTEST_SKIP() << "No " << model(name) << " model is downloaded";
      }
    }
  }

  inline static const std::string MODEL{CTEST_RTMPoseController_MODEL};

  const cv::Mat blank{480, 640, CV_8UC3, cv::Scalar::all(127)};
  RTMPoseController controller;
};

TEST_F(CTEST_RTMPoseController, missing_models_fail_to_init)
{
  EXPECT_FALSE(controller.init("no-such-models"));
}

TEST_F(CTEST_RTMPoseController, nothing_is_estimated_before_the_init)
{
  EXPECT_FALSE(controller.estimate(blank).has_value());
}

TEST_F(CTEST_RTMPoseController, blank_frame_shows_no_body)
{
  skip_without_the_models();
  ASSERT_TRUE(controller.init(MODEL));

  const auto poses = controller.estimate(blank);

  ASSERT_TRUE(poses.has_value());
  EXPECT_TRUE(poses->empty());
}

TEST_F(CTEST_RTMPoseController, pose_model_estimates_the_keypoints_of_a_box)
{
  skip_without_the_models();

  PoseModel pose;

  ASSERT_TRUE(pose.init(model(RTMPoseController::POSE)));

  const auto keypoints = pose.estimate(blank, {100.0F, 50.0F, 200.0F, 400.0F});

  ASSERT_TRUE(keypoints.has_value());
  ASSERT_FALSE(keypoints->empty());

  for (const auto& [position, score] : *keypoints) {
    EXPECT_TRUE(std::isfinite(position.x) && std::isfinite(position.y) &&
                std::isfinite(position.z) && std::isfinite(score));
  }
}
