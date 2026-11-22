#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OPENPOSECONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OPENPOSECONTROLLER_CLASS_H

#include <opencv2/core.hpp>
#include <opencv2/dnn.hpp>
#include <string>

#include "src/MoCap/IPoseEstimator.h"

namespace openpose
{

/**
 * @brief The OpenPose pose estimator. It estimates the 18 COCO keypoints of
 * a body with the OpenPose COCO Caffe model through the OpenCV DNN module.
 *
 * Nothing throws: the failures are logged and reported through the return
 * values.
 */
class OpenPoseController : public mocap::IPoseEstimator
{
 public:
  /// @brief The network and the weights files of the model directory.
  inline static constexpr const char* const NETWORK =
      "pose_deploy_linevec.prototxt";
  inline static constexpr const char* const WEIGHTS =
      "pose_iter_440000.caffemodel";

  /// @brief Loads the NETWORK and the WEIGHTS files of the given directory.
  /// See the mocap::IPoseEstimator interface.
  bool init(const std::string& model) override;

  /// @brief Estimates the pose of the frame. See the mocap::IPoseEstimator
  /// interface.
  result estimate(const cv::Mat& frame) override;

 private:
  /// @brief The model input height, the width keeping the frame aspect ratio
  /// in the multiples of the SIDE_STEP, the OpenPose -1x368 resolution.
  inline static constexpr const double INPUT_HEIGHT = 368.0;
  inline static constexpr const double SIDE_STEP = 16.0;
  /// @brief The model input values are the (pixel - INPUT_MEAN) * INPUT_SCALE
  /// ones.
  inline static constexpr const double INPUT_MEAN = 128.0;
  inline static constexpr const double INPUT_SCALE = 1.0 / 256.0;

  cv::dnn::Net mnetwork;
};

}  // namespace openpose

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OPENPOSECONTROLLER_CLASS_H
