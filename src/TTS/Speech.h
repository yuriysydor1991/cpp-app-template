#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SPEECH_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SPEECH_CLASS_H

#include <chrono>
#include <cstdint>
#include <vector>

/**
 * @brief The engine neutral text to speech subsystem namespace: the speech,
 * the synthesizer interface the speech engines implement and the outputs the
 * speech goes to.
 */
namespace tts
{

/**
 * @brief The synthesized speech: the mono 16-bit PCM samples of the given
 * rate, the very ones the WavWriter writes and the AudioPlayer plays.
 */
class Speech
{
 public:
  using sample = std::int16_t;
  using samples = std::vector<sample>;

  /**
   * @brief Keeps the given speech.
   *
   * @param pcm The mono 16-bit samples of the speech.
   * @param sampleRate The samples count per second.
   */
  Speech(samples pcm, int sampleRate);

  /// @brief Provides the mono 16-bit samples of the speech.
  const samples& get_samples() const;

  /// @brief Provides the samples count per second.
  int get_sample_rate() const;

  /// @brief Provides the time the speech plays for, a zero one for no valid
  /// sample rate.
  std::chrono::milliseconds get_duration() const;

 private:
  samples msamples;
  int msample_rate;
};

}  // namespace tts

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SPEECH_CLASS_H
