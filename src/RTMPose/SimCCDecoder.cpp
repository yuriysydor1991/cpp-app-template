#include "src/RTMPose/SimCCDecoder.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <opencv2/core.hpp>
#include <vector>

namespace rtmpose
{

SimCCDecoder::pose SimCCDecoder::decode(const std::vector<cv::Mat>& axes)
{
  pose keypoints;

  for (int row = 0; row < axes.front().rows; ++row) {
    std::array<float, 3> position{};
    double score = 1.0;

    for (std::size_t axis = 0; axis < std::min<std::size_t>(axes.size(), 3U);
         ++axis) {
      double response = 0.0;
      cv::Point bin;

      cv::minMaxLoc(axes[axis].row(row), nullptr, &response, nullptr, &bin);
      position[axis] = static_cast<float>(bin.x) / SPLIT_RATIO;
      score = axis < 2U ? std::min(score, response) : score;
    }

    if (axes.size() > 2U) {
      const auto depthBins = static_cast<float>(axes[2].cols);

      position[2] =
          (position[2] * SPLIT_RATIO / (depthBins / 2.0F) - 1.0F) * Z_RANGE;
    }

    keypoints.emplace_back(cv::Point3f{position[0], position[1], position[2]},
                           static_cast<float>(score));
  }

  return keypoints;
}

}  // namespace rtmpose
