#include "src/OpenPose/HeatmapDecoder.h"

#include <algorithm>
#include <opencv2/core.hpp>

namespace openpose
{

HeatmapDecoder::poses HeatmapDecoder::decode(const cv::Mat& output,
                                             const cv::Size2f& frame)
{
  const cv::Size map{output.size[3], output.size[2]};
  const cv::Size2f scale{frame.width / static_cast<float>(map.width),
                         frame.height / static_cast<float>(map.height)};
  mocap::IPoseEstimator::pose body;
  float best = 0.0F;

  for (int keypoint = 0; keypoint < KEYPOINTS; ++keypoint) {
    const cv::Range channel[] = {cv::Range{0, 1},
                                 cv::Range{keypoint, keypoint + 1},
                                 cv::Range::all(), cv::Range::all()};
    const cv::Mat heatmap = output(channel).reshape(1, map.height);
    double response = 0.0;
    cv::Point peak;

    cv::minMaxLoc(heatmap, nullptr, &response, nullptr, &peak);

    const auto score = static_cast<float>(response);

    body.emplace_back(
        cv::Point3f{static_cast<float>(peak.x) * scale.width,
                    static_cast<float>(peak.y) * scale.height, 0.0F},
        score);
    best = std::max(best, score);
  }

  return best < MIN_SCORE ? poses{} : poses{body};
}

}  // namespace openpose
