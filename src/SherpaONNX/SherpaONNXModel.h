#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SHERPAONNXMODEL_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SHERPAONNXMODEL_CLASS_H

#include <sherpa-onnx/c-api/cxx-api.h>

#include <filesystem>
#include <initializer_list>
#include <memory>
#include <string>

namespace sherpaonnx
{

/**
 * @brief The text to speech model of the sherpa-onnx a directory keeps, the
 * very one the sherpa-onnx tts-models release archives unpack into. Every
 * model kind configures the sherpa-onnx out of the files of it's own.
 */
class SherpaONNXModel
{
 public:
  using SherpaONNXModelPtr = std::unique_ptr<SherpaONNXModel>;

  virtual ~SherpaONNXModel() = default;
  SherpaONNXModel(const SherpaONNXModel&) = delete;
  SherpaONNXModel& operator=(const SherpaONNXModel&) = delete;

  /**
   * @brief Detects the kind of the model by the files of the given directory:
   * the voices.bin one makes it a KokoroModel, the tokens.txt one a VitsModel
   * (the Piper, the MeloTTS, the MMS ones etc.).
   *
   * @param directory The directory of the model files.
   *
   * @return Returns the model, or nullptr for a directory of no known model.
   */
  static SherpaONNXModelPtr detect(const std::filesystem::path& directory);

  /**
   * @brief Provides the sherpa-onnx configuration of the model, the threads
   * count of the inference included.
   */
  sherpa_onnx::cxx::OfflineTtsConfig configure() const;

 protected:
  /// @brief Keeps the directory of the model files.
  explicit SherpaONNXModel(std::filesystem::path directory);

  /// @brief Fills the model kind part of the sherpa-onnx configuration.
  virtual void configure_model(
      sherpa_onnx::cxx::OfflineTtsModelConfig& config) const = 0;

  /**
   * @brief Provides the neural network of the model: the model.onnx file,
   * the model.int8.onnx one or, as the Piper voices name it after the voice,
   * any other .onnx one.
   *
   * @return Returns the network path, an empty one if there is none.
   */
  std::string network() const;

  /**
   * @brief Provides the comma separated paths of those given files the model
   * directory keeps, the way the sherpa-onnx takes several lexicons.
   */
  std::string existing(std::initializer_list<const char*> names) const;

 private:
  const std::filesystem::path mdirectory;
};

using SherpaONNXModelPtr = SherpaONNXModel::SherpaONNXModelPtr;

}  // namespace sherpaonnx

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SHERPAONNXMODEL_CLASS_H
