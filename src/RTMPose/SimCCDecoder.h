#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SIMCCDECODER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SIMCCDECODER_CLASS_H

#include <opencv2/core.hpp>
#include <vector>

#include "src/MoCap/IPoseEstimator.h"

namespace rtmpose
{

/**
 * @brief Decodes the keypoints out of the SimCC (the coordinate
 * classification) outputs of the RTMPose family models the MMPose way.
 */
class SimCCDecoder
{
 public:
  using pose = mocap::IPoseEstimator::pose;

  /// @brief The SimCC bins per model input pixel.
  inline static constexpr const float SPLIT_RATIO = 2.0F;
  /// @brief The depth range of the RTMW3D models, the MMPose one.
  inline static constexpr const float Z_RANGE = 2.1744869F;

  /**
   * @brief Decodes the keypoints: the bin of the highest response of every
   * axis gives the coordinate, the lower of the x and the y responses gives
   * the score.
   *
   * @param axes The x and the y SimCC outputs of the model, followed by the z
   * one of the 3D models: the matrices of a row per keypoint.
   *
   * @return The keypoints in the model input pixels, the depth of the 3D
   * models in the Z_RANGE around the hips.
   */
  static pose decode(const std::vector<cv::Mat>& axes);
};

}  // namespace rtmpose

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SIMCCDECODER_CLASS_H
