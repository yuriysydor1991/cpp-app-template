#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_ONNXMODEL_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_ONNXMODEL_CLASS_H

#include <onnxruntime_cxx_api.h>

#include <cstdint>
#include <opencv2/core.hpp>
#include <optional>
#include <string>
#include <vector>

/**
 * @brief The ONNX Runtime adaptor subsystem namespace.
 */
namespace onnxi
{

/**
 * @brief The neural network of an ONNX file the ONNX Runtime runs on the CPU.
 *
 * Nothing throws: the failures are logged and reported through the return
 * values.
 */
class ONNXModel
{
 public:
  using shape = std::vector<int64_t>;
  using outputs = std::vector<Ort::Value>;

  /// @brief Loads the model file in place of the previously loaded one.
  bool load(const std::string& path);

  /// @brief The shape of the first model input, -1 for it's dynamic
  /// dimensions, an empty one while no model is loaded.
  const shape& input_shape() const;

  /**
   * @brief Runs the model.
   *
   * @param input The continuous float (CV_32F) or int32 (CV_32S) matrix of
   * the first model input, it's dimensions being the input shape.
   *
   * @return The outputs in the model order, none on a failure.
   */
  outputs run(cv::Mat& input);

  /// @brief Gives the planar (NCHW) float tensor of the interleaved one
  /// channel or multichannel float image.
  static cv::Mat planar(const cv::Mat& image);

 private:
  Ort::Env menv{ORT_LOGGING_LEVEL_WARNING, "ONNXModel"};
  std::optional<Ort::Session> msession;
  std::string minput;
  std::vector<std::string> moutputs;
  std::vector<const char*> moutputNames;
  shape mshape;
};

}  // namespace onnxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_ONNXMODEL_CLASS_H
