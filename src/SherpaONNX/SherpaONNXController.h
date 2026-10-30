#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SHERPAONNXCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SHERPAONNXCONTROLLER_CLASS_H

#include <sherpa-onnx/c-api/cxx-api.h>

#include <optional>
#include <string>

#include "src/STT/ISpeechRecognizer.h"

/**
 * @brief The sherpa-onnx speech recognition adaptor subsystem namespace.
 */
namespace sherpaonnx
{

/**
 * @brief The sherpa-onnx speech recognizer. It recognizes the speech with the
 * NeMo transducer models (the Parakeet TDT, the FastConformer ones etc.) of the
 * sherpa-onnx asr-models release.
 *
 * Nothing throws: the failures are logged and reported through the return
 * values.
 */
class SherpaONNXController : public stt::ISpeechRecognizer
{
 public:
  /**
   * @brief Loads the model in place of the previously loaded one. See the
   * stt::ISpeechRecognizer interface.
   *
   * @param model The directory of the model files: the encoder, the decoder
   * and the joiner .onnx (or .int8.onnx) ones and the tokens.txt one.
   */
  bool init(const std::string& model) override;

  /// @brief Recognizes the text of the given audio. See the
  /// stt::ISpeechRecognizer interface.
  result recognize(const samples& audio) override;

 private:
  std::optional<sherpa_onnx::cxx::OfflineRecognizer> mrecognizer;
};

}  // namespace sherpaonnx

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SHERPAONNXCONTROLLER_CLASS_H
