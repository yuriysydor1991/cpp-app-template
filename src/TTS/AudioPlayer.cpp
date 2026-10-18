#include "src/TTS/AudioPlayer.h"

#include <SDL.h>

#include <algorithm>
#include <chrono>
#include <memory>
#include <thread>

#include "src/log/log.h"

namespace tts
{

bool AudioPlayer::play(const Speech& speech, const stop_check& stopped)
{
  if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
    LOGE("Fail to init the SDL audio subsystem: " << SDL_GetError());
    return false;
  }

  SDL_AudioSpec desired{};
  SDL_AudioSpec obtained{};

  desired.freq = speech.get_sample_rate();
  desired.format = AUDIO_S16SYS;
  desired.channels = 1U;
  desired.samples = static_cast<Uint16>(BUFFER_SAMPLES);

  // No callback makes the SDL play the queued samples, while no allowed
  // changes make it convert them into whatever the device plays.
  const SDL_AudioDeviceID device =
      SDL_OpenAudioDevice(nullptr, SDL_FALSE, &desired, &obtained, 0);

  if (device == 0U) {
    LOGE("Fail to open the default audio playback device: " << SDL_GetError());
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    return false;
  }

  const auto& pcm = speech.get_samples();
  const bool queued =
      SDL_QueueAudio(
          device, pcm.data(),
          static_cast<Uint32>(pcm.size() * sizeof(Speech::sample))) == 0;

  if (queued) {
    LOGD("Playing the " << speech.get_duration().count()
                        << " ms speech through the "
                        << SDL_GetCurrentAudioDriver() << " audio driver");

    SDL_PauseAudioDevice(device, 0);

    while (SDL_GetQueuedAudioSize(device) > 0U && !(stopped && stopped())) {
      std::this_thread::sleep_for(WAIT_STEP);
    }

    // The device still plays the last buffer it took out of the queue.
    std::this_thread::sleep_for(
        std::chrono::milliseconds{std::chrono::seconds{obtained.samples}} /
        std::max(obtained.freq, 1));
  } else {
    LOGE("Fail to queue the speech for the playback: " << SDL_GetError());
  }

  SDL_CloseAudioDevice(device);
  SDL_QuitSubSystem(SDL_INIT_AUDIO);

  return queued;
}

AudioPlayerPtr AudioPlayer::create() { return std::make_shared<AudioPlayer>(); }

}  // namespace tts
