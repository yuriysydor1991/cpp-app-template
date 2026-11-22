#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_POSEMODEL_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_POSEMODEL_CLASS_H

#include <opencv2/core.hpp>
#include <optional>
#include <string>

#include "src/MoCap/IPoseEstimator.h"
#include "src/ONNX/ONNXModel.h"

namespace rtmpose
{

/**
 * @brief The top-down RTMPose family model of the MMDeploy ONNX export: it
 * estimates the keypoints of a person box of a frame.
 */
class PoseModel
{
 public:
  using pose = mocap::IPoseEstimator::pose;

  /// @brief Loads the ONNX model file.
  bool init(const std::string& model);

  /// @brief Estimates the keypoints of the box of the BGR frame in the frame
  /// pixels, nothing if no model is loaded or the estimation fails.
  std::optional<pose> estimate(const cv::Mat& frame, const cv::Rect2f& box);

 private:
  /// @brief The RGB channel means and deviations the model input is
  /// normalized with.
  inline static const cv::Scalar MEAN{123.675, 116.28, 103.53};
  inline static const cv::Scalar DEVIATION{58.395, 57.12, 57.375};

  onnxi::ONNXModel mmodel;
};

}  // namespace rtmpose

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_POSEMODEL_CLASS_H
