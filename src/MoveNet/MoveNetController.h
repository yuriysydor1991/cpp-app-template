#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MOVENETCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MOVENETCONTROLLER_CLASS_H

#include <opencv2/core.hpp>
#include <string>

#include "src/MoCap/IPoseEstimator.h"
#include "src/ONNX/ONNXModel.h"

namespace movenet
{

/**
 * @brief The MoveNet pose estimator. It estimates the 17 COCO keypoints of
 * up to six bodies with the MoveNet MultiPose ONNX model.
 *
 * Nothing throws: the failures are logged and reported through the return
 * values.
 */
class MoveNetController : public mocap::IPoseEstimator
{
 public:
  /// @brief Loads the MoveNet MultiPose ONNX model file. See the
  /// mocap::IPoseEstimator interface.
  bool init(const std::string& model) override;

  /// @brief Estimates the poses of the frame. See the mocap::IPoseEstimator
  /// interface.
  result estimate(const cv::Mat& frame) override;

 private:
  /// @brief The longer side of the model input, the shorter one being padded
  /// up to the multiple of the SIDE_STEP.
  inline static constexpr const float MAX_SIDE = 256.0F;
  inline static constexpr const int SIDE_STEP = 32;

  onnxi::ONNXModel mmodel;
};

}  // namespace movenet

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MOVENETCONTROLLER_CLASS_H
