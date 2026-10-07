#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_DARKNETIMAGE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_DARKNETIMAGE_CLASS_H

#include <src/darknet.h>

#include <opencv2/core/mat.hpp>

namespace darknetxxi
{

/**
 * @brief The owner of a Darknet image: the planar RGB floats of the 0-1 range
 * the network computes with.
 */
class DarknetImage
{
 public:
  virtual ~DarknetImage();

  /// @brief Converts the 8 bits BGR image, the cv::imread() one.
  explicit DarknetImage(const cv::Mat& bgr);

  DarknetImage(const DarknetImage&) = delete;
  DarknetImage& operator=(const DarknetImage&) = delete;

  /**
   * @brief Makes the network input of the image: the copy of the given size,
   * the letterboxed one keeping the aspect ratio of the image.
   */
  DarknetImage resized(int width, int height, bool letterbox) const;

  const image& get() const;

 private:
  explicit DarknetImage(image owned);

  image mimage;
};

}  // namespace darknetxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DARKNETIMAGE_CLASS_H
