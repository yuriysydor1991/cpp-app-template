#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_ISPEECHRECOGNIZER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_ISPEECHRECOGNIZER_CLASS_H

#include <memory>
#include <optional>
#include <string>
#include <vector>

/**
 * @brief The engine neutral speech recognition subsystem namespace.
 */
namespace stt
{

/**
 * @brief The interface every speech recognition engine of the project
 * implements: it loads a model and recognizes the text of the given audio.
 *
 * The engines report their failures through the return values and the
 * project log instead of throwing.
 */
class ISpeechRecognizer
{
 public:
  using result = std::optional<std::string>;
  using samples = std::vector<float>;
  using ISpeechRecognizerPtr = std::shared_ptr<ISpeechRecognizer>;

  /// @brief The samples count per second of the audio every engine takes.
  inline static constexpr const int SAMPLE_RATE = 16000;

  virtual ~ISpeechRecognizer() = default;
  ISpeechRecognizer() = default;
  ISpeechRecognizer(const ISpeechRecognizer&) = delete;
  ISpeechRecognizer& operator=(const ISpeechRecognizer&) = delete;

  /**
   * @brief Loads the model in place of the previously loaded one.
   *
   * @param model The model of the engine: a file, a directory etc., whatever
   * the engine keeps it's models in.
   *
   * @return Returns true on success and false otherwise.
   */
  virtual bool init(const std::string& model) = 0;

  /**
   * @brief Recognizes the text of the given audio.
   *
   * @param audio The mono samples of the SAMPLE_RATE rate.
   *
   * @return Returns the recognized text, the empty one for no speech, or
   * nothing if no model is loaded or the recognition fails.
   */
  virtual result recognize(const samples& audio) = 0;

  /**
   * @brief Creates the recognizer of the speech engine the build links in.
   * The engine sources of the flavor define it, so swapping the engine
   * leaves the callers untouched.
   *
   * @return The created recognizer.
   */
  static ISpeechRecognizerPtr create();
};

using ISpeechRecognizerPtr = ISpeechRecognizer::ISpeechRecognizerPtr;

}  // namespace stt

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_ISPEECHRECOGNIZER_CLASS_H
