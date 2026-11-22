#include "src/MoveNet/MoveNetDecoder.h"

#include <cstddef>
#include <opencv2/core.hpp>

namespace movenet
{

MoveNetDecoder::poses MoveNetDecoder::decode(const float* output,
                                             const cv::Size2f& scale)
{
  poses bodies;

  for (std::size_t body = 0; body < BODIES; ++body) {
    const float* values = output + (body * BODY_VALUES);

    if (values[BODY_VALUES - 1U] < MIN_BODY_SCORE) {
      continue;
    }

    auto& pose = bodies.emplace_back();

    for (std::size_t point = 0; point < KEYPOINTS; ++point) {
      const float* keypoint = values + (point * KEYPOINT_VALUES);

      pose.emplace_back(cv::Point3f{keypoint[1] * scale.width,
                                    keypoint[0] * scale.height, 0.0F},
                        keypoint[2]);
    }
  }

  return bodies;
}

}  // namespace movenet
