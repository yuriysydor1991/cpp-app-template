#include "src/OpenPose/OpenPoseController.h"

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/dnn.hpp>
#include <string>

#include "src/MoCap/IPoseEstimator.h"
#include "src/OpenPose/HeatmapDecoder.h"
#include "src/log/log.h"

namespace mocap
{

IPoseEstimatorPtr IPoseEstimator::create()
{
  return std::make_shared<openpose::OpenPoseController>();
}

}  // namespace mocap

namespace openpose
{

bool OpenPoseController::init(const std::string& model)
{
  const std::filesystem::path directory{model};

  try {
    mnetwork = cv::dnn::readNetFromCaffe((directory / NETWORK).string(),
                                         (directory / WEIGHTS).string());
  }
  catch (const cv::Exception& error) {
    mnetwork = {};
    LOGE("Fail to load the " << model << " OpenPose model: " << error.what());
  }

  return !mnetwork.empty();
}

OpenPoseController::result OpenPoseController::estimate(const cv::Mat& frame)
{
  if (mnetwork.empty()) {
    LOGE("No OpenPose model is loaded");
    return {};
  }

  if (frame.empty() || frame.type() != CV_8UC3) {
    LOGE("OpenPose estimates the poses of the BGR frames only");
    return {};
  }

  const double width = std::max(1.0, std::round(INPUT_HEIGHT * frame.cols /
                                                frame.rows / SIDE_STEP)) *
                       SIDE_STEP;

  mnetwork.setInput(cv::dnn::blobFromImage(
      frame, INPUT_SCALE,
      cv::Size{static_cast<int>(width), static_cast<int>(INPUT_HEIGHT)},
      cv::Scalar::all(INPUT_MEAN), false, false));

  try {
    return HeatmapDecoder::decode(mnetwork.forward(), frame.size());
  }
  catch (const cv::Exception& error) {
    LOGE("Fail to run the OpenPose model: " << error.what());
    return {};
  }
}

}  // namespace openpose
