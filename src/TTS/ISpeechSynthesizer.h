#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_ISPEECHSYNTHESIZER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_ISPEECHSYNTHESIZER_CLASS_H

#include <memory>
#include <optional>
#include <string>

#include "src/TTS/Speech.h"

namespace tts
{

/**
 * @brief The interface every speech engine of the project implements: it
 * speaks the given text with the given voice into the Speech.
 *
 * The engines report their failures through the return values and the
 * project log instead of throwing.
 */
class ISpeechSynthesizer
{
 public:
  using result = std::optional<Speech>;
  using ISpeechSynthesizerPtr = std::shared_ptr<ISpeechSynthesizer>;

  virtual ~ISpeechSynthesizer() = default;
  ISpeechSynthesizer() = default;
  ISpeechSynthesizer(const ISpeechSynthesizer&) = delete;
  ISpeechSynthesizer& operator=(const ISpeechSynthesizer&) = delete;

  /**
   * @brief Synthesizes the speech of the given text.
   *
   * @param text The UTF-8 text to speak.
   * @param voice The voice of the engine to speak with: a voice name, a model
   * path etc., whatever the engine identifies it's voices by.
   *
   * @return Returns the synthesized speech, or nothing if the engine fails to
   * initialize, knows no such voice or fails to synthesize the speech.
   */
  virtual result synthesize(const std::string& text,
                            const std::string& voice) = 0;

  /**
   * @brief Creates the synthesizer of the speech engine the build links in.
   * The engine sources define it (the src/SherpaONNX/SherpaONNXController.cpp
   * file does), so swapping the engine leaves the callers untouched.
   *
   * @return The created synthesizer.
   */
  static ISpeechSynthesizerPtr create();
};

using ISpeechSynthesizerPtr = ISpeechSynthesizer::ISpeechSynthesizerPtr;

}  // namespace tts

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_ISPEECHSYNTHESIZER_CLASS_H
