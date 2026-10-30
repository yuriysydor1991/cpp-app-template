#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SPEECHLISTENER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SPEECHLISTENER_CLASS_H

#include <chrono>
#include <memory>
#include <string>

#include "src/STT/ISpeechRecognizer.h"
#include "src/STT/Microphone.h"
#include "src/STT/UtteranceDetector.h"

namespace stt
{

/**
 * @brief Listens to the microphone and recognizes the utterances it hears.
 *
 * The Microphone captures the audio, the UtteranceDetector cuts it into the
 * utterances at the pauses of the speech and the ISpeechRecognizer turns every
 * utterance into the text. Nothing throws: the failures are logged and
 * reported through the return values.
 */
class SpeechListener
{
 public:
  using result = ISpeechRecognizer::result;
  using SpeechListenerPtr = std::shared_ptr<SpeechListener>;

  ~SpeechListener() = default;
  SpeechListener(ISpeechRecognizerPtr recognizer, MicrophonePtr microphone);
  SpeechListener(const SpeechListener&) = delete;
  SpeechListener& operator=(const SpeechListener&) = delete;

  /**
   * @brief Loads the model of the recognizer. See the ISpeechRecognizer::init
   * method.
   */
  bool init(const std::string& model);

  /**
   * @brief Listens to the microphone for the LISTEN_STEP time and recognizes
   * the utterance completed meanwhile. The very first call opens the
   * microphone.
   *
   * @return Returns the text of the completed utterance, the empty one while
   * nothing complete is said, or nothing if no model is loaded, the
   * microphone fails to open or the recognition fails.
   */
  result listen();

  /**
   * @brief Creates a listener of the default microphone and the recognizer of
   * the engine the build links in. Call the SpeechListener::init method before
   * the listening.
   */
  static SpeechListenerPtr create();

 private:
  /// @brief The audio the microphone captures in between of the utterance
  /// checks.
  inline static constexpr const std::chrono::milliseconds LISTEN_STEP{100};

  const ISpeechRecognizerPtr mrecognizer;
  const MicrophonePtr mmicrophone;
  UtteranceDetector mdetector{ISpeechRecognizer::SAMPLE_RATE};
  bool minitialized{false};
};

using SpeechListenerPtr = SpeechListener::SpeechListenerPtr;

}  // namespace stt

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SPEECHLISTENER_CLASS_H
