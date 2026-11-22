#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MOVENETDECODER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MOVENETDECODER_CLASS_H

#include <cstddef>
#include <opencv2/core.hpp>

#include "src/MoCap/IPoseEstimator.h"

/**
 * @brief The MoveNet pose estimation adaptor subsystem namespace.
 */
namespace movenet
{

/**
 * @brief Decodes the poses out of the MoveNet MultiPose output: the BODIES
 * rows of the KEYPOINTS (y, x, score) triples normalized to the model input,
 * each followed by the body box (ymin, xmin, ymax, xmax) and the body score.
 */
class MoveNetDecoder
{
 public:
  using poses = mocap::IPoseEstimator::poses;

  inline static constexpr const std::size_t BODIES = 6U;
  inline static constexpr const std::size_t KEYPOINTS = 17U;
  /// @brief The (y, x, score) values of a keypoint.
  inline static constexpr const std::size_t KEYPOINT_VALUES = 3U;
  inline static constexpr const std::size_t BODY_VALUES = 56U;
  /// @brief The least body score of the decoded bodies, the TF.js one.
  inline static constexpr const float MIN_BODY_SCORE = 0.25F;

  /**
   * @brief Decodes the bodies scored MIN_BODY_SCORE at least.
   *
   * @param output The BODIES * BODY_VALUES model output.
   * @param scale The frame size of the model input.
   */
  static poses decode(const float* output, const cv::Size2f& scale);
};

}  // namespace movenet

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MOVENETDECODER_CLASS_H
