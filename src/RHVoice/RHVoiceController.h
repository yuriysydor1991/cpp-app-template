#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_RHVOICECONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_RHVOICECONTROLLER_CLASS_H

#include <RHVoice.h>

#include <string>

#include "src/TTS/ISpeechSynthesizer.h"

/**
 * @brief The RHVoice speech synthesis adaptor subsystem namespace.
 */
namespace rhvoice
{

/**
 * @brief The RHVoice speech synthesizer. It speaks the text with the installed
 * RHVoice voices (Alan, Slt, Anatol, Natalia etc.) into the speech of the
 * voice sample rate, the 24 kHz one of the most voices.
 *
 * The very first synthesis creates the RHVoice engine, which loads the
 * installed voices, and the controller destruction deletes it. The
 * RHVOICE_DATA_PATH and the RHVOICE_CONFIG_PATH environment variables point at
 * the RHVoice data and configuration in place of the installed ones. Nothing
 * throws: the failures are logged and reported through the return values.
 */
class RHVoiceController : public tts::ISpeechSynthesizer
{
 public:
  ~RHVoiceController() override;
  RHVoiceController() = default;

  /**
   * @brief Synthesizes the speech of the given text. See the
   * tts::ISpeechSynthesizer interface.
   *
   * @param text The UTF-8 text to speak.
   * @param voice The RHVoice voice name (Alan, Anatol etc.) or a voice profile
   * of the voices of different languages (Anatol+Alan etc.).
   *
   * @return Returns the synthesized speech, or nothing if the RHVoice finds no
   * voices, knows no such voice, gets an empty text or fails to synthesize the
   * speech.
   */
  result synthesize(const std::string& text, const std::string& voice) override;

 private:
  /**
   * @brief Creates the RHVoice engine unless it is created already.
   *
   * @return Returns true on success and false otherwise.
   */
  bool init();

  RHVoice_tts_engine engine{nullptr};
};

}  // namespace rhvoice

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_RHVOICECONTROLLER_CLASS_H
