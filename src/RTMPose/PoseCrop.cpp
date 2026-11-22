#include "src/RTMPose/PoseCrop.h"

#include <algorithm>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

namespace rtmpose
{

PoseCrop::PoseCrop(const cv::Rect2f& box, const cv::Size& input)
    : mcenter{(box.tl() + box.br()) / 2},
      minput{input},
      mscale{std::min(static_cast<float>(input.width) / box.width,
                      static_cast<float>(input.height) / box.height) /
             PADDING}
{
}

cv::Mat PoseCrop::warp(const cv::Mat& frame) const
{
  const cv::Point2f half = cv::Size2f{minput} / 2.0F;
  const cv::Matx23f transform{mscale, 0.0F,   half.x - (mscale * mcenter.x),
                              0.0F,   mscale, half.y - (mscale * mcenter.y)};
  cv::Mat crop;

  cv::warpAffine(frame, crop, transform, minput, cv::INTER_LINEAR);

  return crop;
}

cv::Point2f PoseCrop::to_frame(const cv::Point2f& point) const
{
  const cv::Point2f half = cv::Size2f{minput} / 2.0F;

  return (point - half) / mscale + mcenter;
}

}  // namespace rtmpose
