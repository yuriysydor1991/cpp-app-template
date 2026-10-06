#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WHISPERCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WHISPERCONTROLLER_CLASS_H

#include <chrono>
#include <memory>
#include <optional>
#include <string>

#include "src/WhisperCPP/UtteranceDetector.h"

struct whisper_context;

/**
 * @brief The whisper.cpp speech recognition adaptor subsystem namespace.
 */
namespace whisperi
{

class Microphone;

/**
 * @brief The whisper.cpp speech recognition controller. It loads a whisper
 * model, listens to the default microphone of the system and transcribes the
 * utterances it hears into the text.
 *
 * The Microphone class captures the audio, while the UtteranceDetector one
 * cuts it into the utterances at the pauses of the speech. The whisper.cpp and
 * the ggml messages go into the project logger. Nothing throws: the failures
 * are logged and reported through the return values.
 */
class WhisperController
{
 public:
  using result = std::optional<std::string>;
  using samples = UtteranceDetector::samples;
  using WhisperControllerPtr = std::shared_ptr<WhisperController>;

  virtual ~WhisperController();
  WhisperController();
  WhisperController(const WhisperController&) = delete;
  WhisperController& operator=(const WhisperController&) = delete;

  /**
   * @brief Loads the whisper model in place of the previously loaded one.
   *
   * @param modelPath The ggml model file path, e.g. the
   * models/ggml-base.en.bin one.
   * @param language The spoken language code (en, uk, de etc.) a multilingual
   * model transcribes, the auto one to detect it. The English only models
   * transcribe the English whatever it is.
   *
   * @return Returns true on success and false otherwise.
   */
  virtual bool init(const std::string& modelPath, const std::string& language);

  /**
   * @brief Listens to the default microphone for the LISTEN_STEP time and
   * transcribes the utterance completed meanwhile. The very first call opens
   * the microphone.
   *
   * @return Returns the text of the completed utterance, the empty one while
   * nothing complete is said, or nothing if the controller is not initialized,
   * the microphone fails to open or the transcription fails.
   */
  virtual result listen();

  /**
   * @brief Transcribes the given audio into the text.
   *
   * @param audio The mono samples of the 16 kHz rate, the WHISPER_SAMPLE_RATE
   * one.
   *
   * @return Returns the recognized text, the empty one for no speech, or
   * nothing if the controller is not initialized or the transcription fails.
   */
  virtual result transcribe(const samples& audio);

  /**
   * @brief Creates a controller instance. Call the WhisperController::init
   * method before the transcription.
   *
   * @return The created controller.
   */
  static WhisperControllerPtr create();

 private:
  /// @brief The audio the microphone captures in between of the utterance
  /// checks.
  inline static constexpr const std::chrono::milliseconds LISTEN_STEP{100};

  whisper_context* context{nullptr};
  std::string spokenLanguage;
  std::shared_ptr<Microphone> microphone;
  UtteranceDetector detector;
};

using WhisperControllerPtr = WhisperController::WhisperControllerPtr;

}  // namespace whisperi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WHISPERCONTROLLER_CLASS_H
