#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LANDMARKSDECODER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LANDMARKSDECODER_CLASS_H

#include <mediapipe/tasks/c/vision/pose_landmarker/pose_landmarker_result.h>

#include <opencv2/core.hpp>

#include "src/MoCap/IPoseEstimator.h"

/**
 * @brief The MediaPipe pose landmarker adaptor subsystem namespace.
 */
namespace mediapipei
{

/**
 * @brief Decodes the poses out of the normalized landmarks of the MediaPipe
 * pose landmarker result.
 */
class LandmarksDecoder
{
 public:
  using poses = mocap::IPoseEstimator::poses;

  /**
   * @brief Decodes the landmarks of every body into the frame pixels, the
   * depth in the scale of the x axis, the visibility being the score.
   */
  static poses decode(const MpPoseLandmarkerResult& result,
                      const cv::Size2f& frame);
};

}  // namespace mediapipei

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LANDMARKSDECODER_CLASS_H
