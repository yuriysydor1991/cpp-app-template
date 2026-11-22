#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MOTIONCAPTURE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MOTIONCAPTURE_CLASS_H

#include <memory>
#include <opencv2/core.hpp>
#include <string>

#include "src/MoCap/FrameSource.h"
#include "src/MoCap/IPoseEstimator.h"

namespace mocap
{

/**
 * @brief Captures the body motion: estimates the poses of every frame the
 * frame source reads with the pose estimator.
 */
class MotionCapture
{
 public:
  using result = IPoseEstimator::result;
  using MotionCapturePtr = std::shared_ptr<MotionCapture>;

  MotionCapture(IPoseEstimatorPtr estimator, FrameSourcePtr source);
  MotionCapture(const MotionCapture&) = delete;
  MotionCapture& operator=(const MotionCapture&) = delete;

  /// @brief Loads the model of the estimator, see IPoseEstimator::init.
  bool init(const std::string& model);

  /// @brief Opens the input of the frames, see FrameSource::open.
  bool open(const std::string& input);

  /**
   * @brief Estimates the poses of the next frame of the input.
   *
   * @return The poses, or nothing at the end of the input or on a failure.
   */
  result capture();

  /// @brief Creates the capture of a frame source and of the estimator of the
  /// engine the build links in.
  static MotionCapturePtr create();

 private:
  const IPoseEstimatorPtr mestimator;
  const FrameSourcePtr msource;
  cv::Mat mframe;
};

using MotionCapturePtr = MotionCapture::MotionCapturePtr;

}  // namespace mocap

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MOTIONCAPTURE_CLASS_H
