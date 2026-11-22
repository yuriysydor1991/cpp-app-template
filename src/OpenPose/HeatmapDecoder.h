#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_HEATMAPDECODER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_HEATMAPDECODER_CLASS_H

#include <opencv2/core.hpp>

#include "src/MoCap/IPoseEstimator.h"

/**
 * @brief The OpenPose pose estimation adaptor subsystem namespace.
 */
namespace openpose
{

/**
 * @brief Decodes the pose of a single body out of the keypoint heatmaps of
 * the OpenPose COCO model output the way the OpenCV openpose sample does: the
 * highest response of every heatmap gives the keypoint, while the part
 * affinity fields which group the keypoints of several bodies stay unused.
 */
class HeatmapDecoder
{
 public:
  using poses = mocap::IPoseEstimator::poses;

  /// @brief The keypoint heatmaps leading the model output channels.
  inline static constexpr const int KEYPOINTS = 18;
  /// @brief The least keypoint score of a body, the OpenCV sample one.
  inline static constexpr const float MIN_SCORE = 0.1F;

  /**
   * @brief Decodes the body unless no keypoint scores MIN_SCORE at least.
   *
   * @param output The [1, channels, height, width] model output.
   * @param frame The frame size of the model output.
   */
  static poses decode(const cv::Mat& output, const cv::Size2f& frame);
};

}  // namespace openpose

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HEATMAPDECODER_CLASS_H
