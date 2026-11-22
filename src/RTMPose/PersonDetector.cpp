#include "src/RTMPose/PersonDetector.h"

#include <algorithm>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

#include "src/ONNX/ONNXModel.h"
#include "src/log/log.h"

namespace rtmpose
{

bool PersonDetector::init(const std::string& model)
{
  return mmodel.load(model);
}

std::optional<PersonDetector::boxes> PersonDetector::detect(
    const cv::Mat& frame)
{
  const auto& shape = mmodel.input_shape();

  if (shape.size() != 4U) {
    LOGE("No person detection model is loaded");
    return {};
  }

  // The frame is scaled into the top left corner of the model input, the
  // rest of which is the gray YOLOX padding.
  const cv::Size2f input{static_cast<float>(shape[3]),
                         static_cast<float>(shape[2])};
  const cv::Size2f size = frame.size();
  const float ratio =
      std::min(input.width / size.width, input.height / size.height);
  const cv::Size resized{static_cast<int>(size.width * ratio),
                         static_cast<int>(size.height * ratio)};
  cv::Mat canvas(input, CV_8UC3, PADDING);
  cv::Mat image;

  cv::resize(frame, canvas(cv::Rect{{0, 0}, resized}), resized);
  canvas.convertTo(image, CV_32F);

  cv::Mat tensor = onnxi::ONNXModel::planar(image);
  auto outputs = mmodel.run(tensor);

  if (outputs.empty()) {
    return {};
  }

  const auto count = outputs.front().GetTensorTypeAndShapeInfo().GetShape()[1];

  return decode({static_cast<int>(count), DETECTION_VALUES, CV_32F,
                 outputs.front().GetTensorMutableData<float>()},
                ratio);
}

PersonDetector::boxes PersonDetector::decode(const cv::Mat& detections,
                                             const float ratio)
{
  boxes persons;

  for (int row = 0; row < detections.rows; ++row) {
    const auto* box = detections.ptr<float>(row);

    if (box[DETECTION_VALUES - 1] > MIN_SCORE) {
      persons.emplace_back(cv::Point2f{box[0], box[1]} / ratio,
                           cv::Point2f{box[2], box[3]} / ratio);
    }
  }

  return persons;
}

}  // namespace rtmpose
