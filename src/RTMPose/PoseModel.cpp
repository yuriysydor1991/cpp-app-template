#include "src/RTMPose/PoseModel.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <vector>

#include "src/ONNX/ONNXModel.h"
#include "src/RTMPose/PoseCrop.h"
#include "src/RTMPose/SimCCDecoder.h"
#include "src/log/log.h"

namespace rtmpose
{

bool PoseModel::init(const std::string& model) { return mmodel.load(model); }

std::optional<PoseModel::pose> PoseModel::estimate(const cv::Mat& frame,
                                                   const cv::Rect2f& box)
{
  const auto& shape = mmodel.input_shape();

  if (shape.size() != 4U) {
    LOGE("No pose estimation model is loaded");
    return {};
  }

  const PoseCrop crop{box,
                      {static_cast<int>(shape[3]), static_cast<int>(shape[2])}};
  cv::Mat image;

  cv::cvtColor(crop.warp(frame), image, cv::COLOR_BGR2RGB);
  image.convertTo(image, CV_32F);
  cv::subtract(image, MEAN, image);
  cv::divide(image, DEVIATION, image);

  cv::Mat tensor = onnxi::ONNXModel::planar(image);
  auto outputs = mmodel.run(tensor);

  if (outputs.empty()) {
    return {};
  }

  std::vector<cv::Mat> axes;

  for (auto& output : outputs) {
    const auto dimensions = output.GetTensorTypeAndShapeInfo().GetShape();

    axes.emplace_back(static_cast<int>(dimensions[1]),
                      static_cast<int>(dimensions[2]), CV_32F,
                      output.GetTensorMutableData<float>());
  }

  auto keypoints = SimCCDecoder::decode(axes);

  for (auto& [position, score] : keypoints) {
    const cv::Point2f point = crop.to_frame({position.x, position.y});

    position.x = point.x;
    position.y = point.y;
  }

  return keypoints;
}

}  // namespace rtmpose
