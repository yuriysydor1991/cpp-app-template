#include "src/MediaPipe/LandmarksDecoder.h"

#include <mediapipe/tasks/c/vision/pose_landmarker/pose_landmarker_result.h>

#include <opencv2/core.hpp>

namespace mediapipei
{

LandmarksDecoder::poses LandmarksDecoder::decode(
    const MpPoseLandmarkerResult& result, const cv::Size2f& frame)
{
  poses bodies;

  for (const auto* body = result.pose_landmarks;
       body < result.pose_landmarks + result.pose_landmarks_count; ++body) {
    auto& pose = bodies.emplace_back();

    for (const auto* mark = body->landmarks;
         mark < body->landmarks + body->landmarks_count; ++mark) {
      pose.emplace_back(
          cv::Point3f{mark->x * frame.width, mark->y * frame.height,
                      mark->z * frame.width},
          mark->has_visibility ? mark->visibility : 1.0F);
    }
  }

  return bodies;
}

}  // namespace mediapipei
