#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SHERPAONNXCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SHERPAONNXCONTROLLER_CLASS_H

#include <sherpa-onnx/c-api/cxx-api.h>

#include <optional>
#include <string>

#include "src/TTS/ISpeechSynthesizer.h"

/**
 * @brief The sherpa-onnx speech synthesis adaptor subsystem namespace.
 */
namespace sherpaonnx
{

/**
 * @brief The sherpa-onnx speech synthesizer. It speaks the text with the
 * Kokoro and the VITS (Piper, MeloTTS etc.) models of the sherpa-onnx
 * tts-models release into the speech of the model sample rate.
 *
 * The model of the last voice stays loaded, so the next synthesis with it
 * skips the loading. Nothing throws: the failures are logged and reported
 * through the return values.
 */
class SherpaONNXController : public tts::ISpeechSynthesizer
{
 public:
  /**
   * @brief Synthesizes the speech of the given text. See the
   * tts::ISpeechSynthesizer interface.
   *
   * @param text The UTF-8 text to speak.
   * @param voice The directory of the model files, optionally followed by
   * the :<id> speaker id of a multi-speaker model (models/kokoro:3 etc.),
   * the first speaker otherwise.
   *
   * @return Returns the synthesized speech, or nothing if the directory keeps
   * no known model, the model fails to load or has no such speaker.
   */
  result synthesize(const std::string& text, const std::string& voice) override;

 private:
  /**
   * @brief Loads the model of the given directory unless it is loaded
   * already.
   *
   * @return Returns the engine of the model, or nullptr on a failure.
   */
  const sherpa_onnx::cxx::OfflineTts* load(const std::string& directory);

  std::optional<sherpa_onnx::cxx::OfflineTts> mtts;
  std::string mdirectory;
};

}  // namespace sherpaonnx

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SHERPAONNXCONTROLLER_CLASS_H
