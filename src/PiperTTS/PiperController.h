#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PIPERCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PIPERCONTROLLER_CLASS_H

#include <piper.h>

#include <memory>
#include <string>

#include "src/TTS/ISpeechSynthesizer.h"

/**
 * @brief The Piper speech synthesis adaptor subsystem namespace.
 */
namespace pipertts
{

/**
 * @brief The Piper neural speech synthesizer. It speaks the text with the
 * Piper voice models (the en_US-lessac-medium.onnx one etc.) into the speech
 * of the sample rate of the voice.
 *
 * The very first synthesis with a voice loads it, the next ones reuse it,
 * while another voice replaces it. The espeak-ng the Piper phonemizes the text
 * with keeps a single process wide state, so a single voice is loaded at a
 * time. Nothing throws: the failures are logged and reported through the
 * return values.
 */
class PiperController : public tts::ISpeechSynthesizer
{
 public:
  /**
   * @brief Synthesizes the speech of the given text. See the
   * tts::ISpeechSynthesizer interface.
   *
   * @param text The UTF-8 text to speak.
   * @param voice The path of the Piper voice model, the .onnx file with it's
   * .onnx.json config beside it.
   *
   * @return Returns the synthesized speech, or nothing if the voice is
   * missing, fails to load or fails to synthesize the speech.
   */
  result synthesize(const std::string& text, const std::string& voice) override;

 private:
  /**
   * @brief Loads the given voice unless it is loaded already.
   *
   * @return Returns true on success and false otherwise.
   */
  bool load(const std::string& voice);

  /// @brief The path of the loaded voice.
  std::string mvoice;
  std::unique_ptr<piper_synthesizer, decltype(&piper_free)> msynthesizer{
      nullptr, piper_free};
};

}  // namespace pipertts

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PIPERCONTROLLER_CLASS_H
