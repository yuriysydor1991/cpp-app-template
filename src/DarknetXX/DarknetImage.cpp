#include "src/DarknetXX/DarknetImage.h"

#include <src/darknet.h>

#include <cstddef>
#include <limits>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

namespace darknetxxi
{

DarknetImage::~DarknetImage() { free_image(mimage); }

DarknetImage::DarknetImage(const cv::Mat& bgr)
    : mimage{make_image(bgr.cols, bgr.rows, bgr.channels())}
{
  cv::Mat rgb;
  cv::cvtColor(bgr, rgb, cv::COLOR_BGR2RGB);
  rgb.convertTo(rgb, CV_32F, 1.0 / std::numeric_limits<uchar>::max());

  // The planes share the image memory, so the split fills the image itself.
  const auto plane = static_cast<std::ptrdiff_t>(mimage.w) * mimage.h;

  std::vector<cv::Mat> planes;
  planes.reserve(static_cast<std::size_t>(mimage.c));

  for (int channel = 0; channel < mimage.c; ++channel) {
    planes.emplace_back(mimage.h, mimage.w, CV_32F,
                        mimage.data + (channel * plane));
  }

  cv::split(rgb, planes);
}

DarknetImage::DarknetImage(image owned) : mimage{owned} {}

DarknetImage DarknetImage::resized(int width, int height, bool letterbox) const
{
  return DarknetImage{letterbox ? letterbox_image(mimage, width, height)
                                : resize_image(mimage, width, height)};
}

const image& DarknetImage::get() const { return mimage; }

}  // namespace darknetxxi
