#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MICROPHONE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MICROPHONE_CLASS_H

#include <SDL_audio.h>

#include <memory>
#include <vector>

namespace whisperi
{

/**
 * @brief The default microphone of the system captured through the SDL2 audio
 * subsystem.
 *
 * The SDL2 captures the audio on a thread of it's own and queues it, so the
 * Microphone::read calls take the queued samples out at their own pace. The
 * SDL_AUDIODRIVER environment variable picks the audio driver, the demand only
 * dummy and disk ones included.
 */
class Microphone
{
 public:
  using samples = std::vector<float>;
  using MicrophonePtr = std::shared_ptr<Microphone>;

  virtual ~Microphone();
  Microphone() = default;
  Microphone(const Microphone&) = delete;
  Microphone& operator=(const Microphone&) = delete;

  /**
   * @brief Opens the default capture device of the system and starts
   * capturing the mono samples of the given rate. The calls after a successful
   * one do nothing.
   *
   * @param sampleRate The samples count per second to capture.
   *
   * @return Returns true on success and false otherwise.
   */
  virtual bool open(int sampleRate);

  /**
   * @brief Takes the samples captured since the previous call out of the
   * queue.
   *
   * @return Returns the captured samples, empty while the device is not opened
   * or has captured nothing yet.
   */
  virtual samples read();

  static MicrophonePtr create();

 private:
  /// @brief The samples count of a single capture by the device, which keeps
  /// it 64 ms long at the 16 kHz rate.
  inline static constexpr const Uint16 BUFFER_SAMPLES = 1024U;

  SDL_AudioDeviceID device{0U};
};

using MicrophonePtr = Microphone::MicrophonePtr;

}  // namespace whisperi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MICROPHONE_CLASS_H
