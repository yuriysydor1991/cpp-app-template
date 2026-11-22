#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_RTMPOSECONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_RTMPOSECONTROLLER_CLASS_H

#include <opencv2/core.hpp>
#include <string>

#include "src/MoCap/IPoseEstimator.h"
#include "src/RTMPose/PersonDetector.h"
#include "src/RTMPose/PoseModel.h"

namespace rtmpose
{

/**
 * @brief The top-down RTMPose family pose estimator: the YOLOX detector finds
 * the persons of the frame and the pose model estimates the keypoints of
 * every one of them.
 *
 * Nothing throws: the failures are logged and reported through the return
 * values.
 */
class RTMPoseController : public mocap::IPoseEstimator
{
 public:
  /// @brief The ONNX models of the model directory.
  inline static constexpr const char* const DETECTOR = "detector.onnx";
  inline static constexpr const char* const POSE = "pose.onnx";

  /// @brief Loads the DETECTOR and the POSE models of the given directory.
  /// See the mocap::IPoseEstimator interface.
  bool init(const std::string& model) override;

  /// @brief Estimates the poses of the frame. See the mocap::IPoseEstimator
  /// interface.
  result estimate(const cv::Mat& frame) override;

 private:
  PersonDetector mdetector;
  PoseModel mpose;
};

}  // namespace rtmpose

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_RTMPOSECONTROLLER_CLASS_H
