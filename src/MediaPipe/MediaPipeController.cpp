#include "src/MediaPipe/MediaPipeController.h"

#include <mediapipe/tasks/c/core/common.h>
#include <mediapipe/tasks/c/vision/core/image.h>
#include <mediapipe/tasks/c/vision/pose_landmarker/pose_landmarker.h>

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

#include "src/MediaPipe/LandmarksDecoder.h"
#include "src/MoCap/IPoseEstimator.h"
#include "src/log/log.h"

namespace mocap
{

IPoseEstimatorPtr IPoseEstimator::create()
{
  return std::make_shared<mediapipei::MediaPipeController>();
}

}  // namespace mocap

namespace mediapipei
{

bool MediaPipeController::init(const std::string& model)
{
  MpPoseLandmarkerOptions options{};
  MpPoseLandmarkerPtr landmarker{nullptr};
  char* error{nullptr};

  // The video mode tracks the bodies of the successive frames.
  options.base_options.model_asset_path = model.c_str();
  options.running_mode = MP_RUNNING_MODE_VIDEO;
  options.num_poses = MAX_BODIES;

  const bool created =
      succeeded(MpPoseLandmarkerCreate(&options, &landmarker, &error), error,
                "MpPoseLandmarkerCreate");

  mlandmarker.reset(created ? landmarker : nullptr);

  return created;
}

MediaPipeController::result MediaPipeController::estimate(const cv::Mat& frame)
{
  if (!mlandmarker) {
    LOGE("No MediaPipe pose landmarker model is loaded");
    return {};
  }

  if (frame.empty() || frame.type() != CV_8UC3) {
    LOGE("MediaPipe estimates the poses of the BGR frames only");
    return {};
  }

  cv::Mat rgb;
  MpImagePtr created{nullptr};
  char* error{nullptr};

  cv::cvtColor(frame, rgb, cv::COLOR_BGR2RGB);

  if (!succeeded(
          MpImageCreateFromUint8Data(
              kMpImageFormatSrgb, rgb.cols, rgb.rows, rgb.data,
              static_cast<int>(rgb.total() * rgb.elemSize()), &created, &error),
          error, "MpImageCreateFromUint8Data")) {
    return {};
  }

  const std::unique_ptr<MpImageInternal, void (*)(MpImagePtr)> image{
      created, &MpImageFree};
  const int64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(
                          std::chrono::steady_clock::now().time_since_epoch())
                          .count();
  MpPoseLandmarkerResult landmarks{};

  mtimestamp = std::max(mtimestamp + 1, now);

  if (!succeeded(MpPoseLandmarkerDetectForVideo(mlandmarker.get(), image.get(),
                                                nullptr, mtimestamp, &landmarks,
                                                &error),
                 error, "MpPoseLandmarkerDetectForVideo")) {
    return {};
  }

  auto bodies = LandmarksDecoder::decode(landmarks, frame.size());

  MpPoseLandmarkerCloseResult(&landmarks);

  return bodies;
}

bool MediaPipeController::succeeded(const MpStatus status, char*& error,
                                    const char* call)
{
  if (status != kMpOk) {
    LOGE("The " << call << " call fails: " << (error ? error : "no message"));
  }

  MpErrorFree(error);
  error = nullptr;

  return status == kMpOk;
}

}  // namespace mediapipei
