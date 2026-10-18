#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_AUDIOPLAYER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_AUDIOPLAYER_CLASS_H

#include <chrono>
#include <functional>
#include <memory>

#include "src/TTS/Speech.h"

namespace tts
{

/**
 * @brief Plays the speech through the default audio playback device of the
 * system with the SDL2 audio subsystem.
 *
 * The SDL2 plays the queued samples on a thread of it's own, while the
 * AudioPlayer::play call waits for them to be played. The SDL_AUDIODRIVER
 * environment variable picks the audio driver, the demand only dummy and disk
 * ones included, so the playback needs no sound card for the tests.
 */
class AudioPlayer
{
 public:
  using AudioPlayerPtr = std::shared_ptr<AudioPlayer>;
  using stop_check = std::function<bool()>;

  virtual ~AudioPlayer() = default;
  AudioPlayer() = default;

  /**
   * @brief Plays the given speech and waits till the device plays it out.
   *
   * @param speech The speech to play.
   * @param stopped Tells if the playback is asked to stop before the speech
   * end, the Ctrl+C keys for example. An empty one plays the whole speech.
   *
   * @return Returns true if the speech is played or stopped and false if the
   * playback device fails to open or to take the speech.
   */
  virtual bool play(const Speech& speech, const stop_check& stopped);

  static AudioPlayerPtr create();

 private:
  /// @brief The samples count of a single device buffer, which keeps it 46 ms
  /// long at the 22.05 kHz rate.
  inline static constexpr const unsigned BUFFER_SAMPLES = 1024U;

  /// @brief The time in between of the played out checks.
  inline static constexpr const std::chrono::milliseconds WAIT_STEP{10};
};

using AudioPlayerPtr = AudioPlayer::AudioPlayerPtr;

}  // namespace tts

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_AUDIOPLAYER_CLASS_H
