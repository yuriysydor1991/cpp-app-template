#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_ESPEAKNGCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_ESPEAKNGCONTROLLER_CLASS_H

#include <string>

#include "src/TTS/ISpeechSynthesizer.h"

/**
 * @brief The eSpeak NG speech synthesis adaptor subsystem namespace.
 */
namespace espeakng
{

/**
 * @brief The eSpeak NG speech synthesizer. It speaks the text with the voices
 * of the eSpeak NG data (en, uk, de, en-us etc.) into the 22.05 kHz speech.
 *
 * The eSpeak NG keeps a single process wide state, so the very first
 * synthesis initializes it in the synchronous mode, where the synthesis call
 * returns with the whole speech collected, and the controller destruction
 * terminates it. The ESPEAK_DATA_PATH environment variable points at the
 * eSpeak NG data in place of the installed one. Nothing throws: the failures
 * are logged and reported through the return values.
 */
class ESpeakNGController : public tts::ISpeechSynthesizer
{
 public:
  ~ESpeakNGController() override;
  ESpeakNGController() = default;

  /**
   * @brief Synthesizes the speech of the given text. See the
   * tts::ISpeechSynthesizer interface.
   *
   * @param text The UTF-8 text to speak.
   * @param voice The eSpeak NG voice name, the language code (en, uk etc.)
   * one or the full one (gmw/en-US etc.), the espeak-ng --voices command lists
   * them.
   *
   * @return Returns the synthesized speech, or nothing if the eSpeak NG fails
   * to initialize, knows no such voice or fails to synthesize the speech.
   */
  result synthesize(const std::string& text, const std::string& voice) override;

 private:
  /**
   * @brief Initializes the eSpeak NG unless it is initialized already.
   *
   * @return Returns true on success and false otherwise.
   */
  bool init();

  bool initialized{false};
};

}  // namespace espeakng

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_ESPEAKNGCONTROLLER_CLASS_H
