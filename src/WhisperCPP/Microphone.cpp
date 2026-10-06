#include "src/WhisperCPP/Microphone.h"

#include <SDL.h>

#include <memory>

#include "src/log/log.h"

namespace whisperi
{

Microphone::~Microphone()
{
  if (device != 0U) {
    SDL_CloseAudioDevice(device);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
  }
}

bool Microphone::open(const int sampleRate)
{
  if (device != 0U) {
    return true;
  }

  if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
    LOGE("Fail to init the SDL audio subsystem: " << SDL_GetError());
    return false;
  }

  SDL_AudioSpec desired{};

  desired.freq = sampleRate;
  desired.format = AUDIO_F32SYS;
  desired.channels = 1U;
  desired.samples = BUFFER_SAMPLES;

  // No callback makes the SDL queue the captured audio for the read calls,
  // while no obtained spec makes it convert whatever the device captures into
  // the desired one.
  device = SDL_OpenAudioDevice(nullptr, SDL_TRUE, &desired, nullptr, 0);

  if (device == 0U) {
    LOGE("Fail to open the default microphone: " << SDL_GetError());
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    return false;
  }

  SDL_PauseAudioDevice(device, 0);

  LOGD("Capturing the default microphone through the "
       << SDL_GetCurrentAudioDriver() << " audio driver");

  return true;
}

Microphone::samples Microphone::read()
{
  if (device == 0U) {
    return {};
  }

  samples captured(SDL_GetQueuedAudioSize(device) / sizeof(float));

  // The capture goes on meanwhile, so no more than the queued size of the
  // call above gets taken out.
  captured.resize(
      SDL_DequeueAudio(device, captured.data(),
                       static_cast<Uint32>(captured.size() * sizeof(float))) /
      sizeof(float));

  return captured;
}

MicrophonePtr Microphone::create() { return std::make_shared<Microphone>(); }

}  // namespace whisperi
