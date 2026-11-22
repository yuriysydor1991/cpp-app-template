#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FRAMESOURCE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FRAMESOURCE_CLASS_H

#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <string>

namespace mocap
{

/**
 * @brief Reads the frames of a camera, an image, an image sequence, a video
 * file or a stream through the OpenCV videoio module.
 */
class FrameSource
{
 public:
  using FrameSourcePtr = std::shared_ptr<FrameSource>;

  /**
   * @brief Opens the camera of the given index ("0" is the default one) or
   * the image, the image sequence ("frame_%03d.png"), the video file or the
   * stream URL of the given input in place of the previously opened one.
   */
  bool open(const std::string& input);

  /// @brief Reads the next frame, false at the end of the input or on a
  /// failure.
  bool read(cv::Mat& frame);

  static FrameSourcePtr create();

 private:
  cv::VideoCapture mcapture;
};

using FrameSourcePtr = FrameSource::FrameSourcePtr;

}  // namespace mocap

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FRAMESOURCE_CLASS_H
