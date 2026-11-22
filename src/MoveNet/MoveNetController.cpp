#include "src/MoveNet/MoveNetController.h"

#include <algorithm>
#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

#include "src/MoCap/IPoseEstimator.h"
#include "src/MoveNet/MoveNetDecoder.h"
#include "src/log/log.h"

namespace mocap
{

IPoseEstimatorPtr IPoseEstimator::create()
{
  return std::make_shared<movenet::MoveNetController>();
}

}  // namespace mocap

namespace movenet
{

bool MoveNetController::init(const std::string& model)
{
  return mmodel.load(model);
}

MoveNetController::result MoveNetController::estimate(const cv::Mat& frame)
{
  if (frame.empty() || frame.type() != CV_8UC3) {
    LOGE("MoveNet estimates the poses of the BGR frames only");
    return {};
  }

  // The model takes the RGB frame of the longer MAX_SIDE side, the shorter
  // one padded up to the multiple of the SIDE_STEP.
  const cv::Size2f size = frame.size();
  const float ratio = MAX_SIDE / std::max(size.width, size.height);
  const cv::Size resized{std::max(1, cvRound(size.width * ratio)),
                         std::max(1, cvRound(size.height * ratio))};
  const cv::Size padded{
      (resized.width + SIDE_STEP - 1) / SIDE_STEP * SIDE_STEP,
      (resized.height + SIDE_STEP - 1) / SIDE_STEP * SIDE_STEP};
  cv::Mat image(padded, CV_8UC3, cv::Scalar::all(0));
  cv::Mat input;

  cv::resize(frame, image(cv::Rect{{0, 0}, resized}), resized);
  cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
  image.convertTo(input, CV_32S);
  input = input.reshape(1, {1, padded.height, padded.width, 3});

  const auto outputs = mmodel.run(input);

  if (outputs.empty()) {
    return {};
  }

  const cv::Size2f paddedSize = padded;
  const cv::Size2f resizedSize = resized;

  return MoveNetDecoder::decode(
      outputs.front().GetTensorData<float>(),
      {paddedSize.width * size.width / resizedSize.width,
       paddedSize.height * size.height / resizedSize.height});
}

}  // namespace movenet
