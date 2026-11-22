#include "src/RTMPose/RTMPoseController.h"

#include <filesystem>
#include <memory>
#include <opencv2/core.hpp>
#include <string>
#include <utility>

#include "src/MoCap/IPoseEstimator.h"
#include "src/log/log.h"

namespace mocap
{

IPoseEstimatorPtr IPoseEstimator::create()
{
  return std::make_shared<rtmpose::RTMPoseController>();
}

}  // namespace mocap

namespace rtmpose
{

bool RTMPoseController::init(const std::string& model)
{
  const std::filesystem::path directory{model};

  return mdetector.init((directory / DETECTOR).string()) &&
         mpose.init((directory / POSE).string());
}

RTMPoseController::result RTMPoseController::estimate(const cv::Mat& frame)
{
  if (frame.empty() || frame.type() != CV_8UC3) {
    LOGE("RTMPose estimates the poses of the BGR frames only");
    return {};
  }

  const auto persons = mdetector.detect(frame);

  if (!persons.has_value()) {
    return {};
  }

  poses bodies;

  for (const auto& box : *persons) {
    auto keypoints = mpose.estimate(frame, box);

    if (!keypoints.has_value()) {
      return {};
    }

    bodies.push_back(std::move(*keypoints));
  }

  return bodies;
}

}  // namespace rtmpose
