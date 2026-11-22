#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MEDIAPIPECONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MEDIAPIPECONTROLLER_CLASS_H

#include <mediapipe/tasks/c/vision/pose_landmarker/pose_landmarker.h>

#include <cstdint>
#include <memory>
#include <opencv2/core.hpp>
#include <string>

#include "src/MoCap/IPoseEstimator.h"

namespace mediapipei
{

/**
 * @brief The MediaPipe Pose estimator. It tracks the 33 BlazePose landmarks
 * of up to MAX_BODIES bodies across the frames with the pose landmarker of
 * the MediaPipe Tasks C API.
 *
 * Nothing throws: the failures are logged and reported through the return
 * values.
 */
class MediaPipeController : public mocap::IPoseEstimator
{
 public:
  inline static constexpr const int MAX_BODIES = 4;

  /// @brief Loads the pose landmarker .task model file. See the
  /// mocap::IPoseEstimator interface.
  bool init(const std::string& model) override;

  /// @brief Estimates the poses of the next frame of the video. See the
  /// mocap::IPoseEstimator interface.
  result estimate(const cv::Mat& frame) override;

 private:
  /// @brief Logs the error message of the failed call and frees it.
  static bool succeeded(MpStatus status, char*& error, const char* call);

  std::unique_ptr<MpPoseLandmarkerInternal, void (*)(MpPoseLandmarkerPtr)>
      mlandmarker{nullptr, [](MpPoseLandmarkerPtr landmarker) {
                    MpPoseLandmarkerClose(landmarker, nullptr);
                  }};
  /// @brief The strictly increasing video timestamp of the last frame.
  int64_t mtimestamp{0};
};

}  // namespace mediapipei

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MEDIAPIPECONTROLLER_CLASS_H
