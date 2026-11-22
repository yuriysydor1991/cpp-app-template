#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_POSECROP_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_POSECROP_CLASS_H

#include <opencv2/core.hpp>

namespace rtmpose
{

/**
 * @brief The crop of the person box the top-down pose model takes: the box
 * padded by the PADDING and widened to the aspect ratio of the model input,
 * scaled into the model input around it's center.
 */
class PoseCrop
{
 public:
  inline static constexpr const float PADDING = 1.25F;

  PoseCrop(const cv::Rect2f& box, const cv::Size& input);

  /// @brief Gives the model input image of the box of the frame.
  cv::Mat warp(const cv::Mat& frame) const;

  /// @brief Maps the point of the model input to the frame.
  cv::Point2f to_frame(const cv::Point2f& point) const;

 private:
  cv::Point2f mcenter;
  cv::Size minput;
  /// @brief The model input pixels per frame pixel.
  float mscale;
};

}  // namespace rtmpose

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_POSECROP_CLASS_H
