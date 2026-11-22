#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PERSONDETECTOR_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PERSONDETECTOR_CLASS_H

#include <opencv2/core.hpp>
#include <optional>
#include <string>
#include <vector>

#include "src/ONNX/ONNXModel.h"

/**
 * @brief The RTMPose pose estimation adaptor subsystem namespace.
 */
namespace rtmpose
{

/**
 * @brief Detects the persons of a frame with the YOLOX ONNX model of the
 * MMDeploy export, the non-maximum suppression included.
 */
class PersonDetector
{
 public:
  using boxes = std::vector<cv::Rect2f>;

  /// @brief The least score of the detected persons, the rtmlib one.
  inline static constexpr const float MIN_SCORE = 0.3F;
  /// @brief The (x1, y1, x2, y2, score) values of a detection.
  inline static constexpr const int DETECTION_VALUES = 5;

  /// @brief Loads the YOLOX ONNX model file.
  bool init(const std::string& model);

  /// @brief Detects the persons of the BGR frame: their boxes, or nothing
  /// if no model is loaded or the detection fails.
  std::optional<boxes> detect(const cv::Mat& frame);

  /**
   * @brief Decodes the boxes of the persons scored above the MIN_SCORE.
   *
   * @param detections The rows of the DETECTION_VALUES in the model input
   * pixels.
   * @param ratio The model input pixels per frame pixel.
   */
  static boxes decode(const cv::Mat& detections, float ratio);

 private:
  /// @brief The gray YOLOX padding of the model input.
  inline static const cv::Scalar PADDING{114.0, 114.0, 114.0};

  onnxi::ONNXModel mmodel;
};

}  // namespace rtmpose

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PERSONDETECTOR_CLASS_H
