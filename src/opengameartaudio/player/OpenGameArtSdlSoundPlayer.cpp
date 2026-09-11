#include "src/opengameartaudio/player/OpenGameArtSdlSoundPlayer.h"

#include <SDL2/SDL.h>

#include <cassert>
#include <memory>
#include <string>

#include "src/log/log.h"
#include "src/opengameartaudio/OpenGameArtSound.h"
#include "src/opengameartaudio/player/IOpenGameArtSoundPlayer.h"

namespace opengameartaudio
{

OpenGameArtSdlSoundPlayer::OpenGameArtSdlSoundPlayer()
{
  if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
    LOGE("Fail to bring the SDL2 audio subsystem up: " << SDL_GetError());
    return;
  }

  minitialized = true;

  LOGD("The SDL2 audio driver in use: " << SDL_GetCurrentAudioDriver());
}

OpenGameArtSdlSoundPlayer::~OpenGameArtSdlSoundPlayer()
{
  if (minitialized) {
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
  }
}

bool OpenGameArtSdlSoundPlayer::supports(const std::string& extension) const
{
  return extension == SUPPORTED_EXTENSION;
}

bool OpenGameArtSdlSoundPlayer::play(const OpenGameArtSoundPtr& sound)
{
  assert(sound != nullptr);

  if (sound == nullptr) {
    LOGE("No sound to play");
    return false;
  }

  if (!minitialized) {
    LOGE("No SDL2 audio subsystem to play the " << sound->alias()
                                                << " sound with");
    return false;
  }

  if (!supports(sound->extension())) {
    LOGW("The bare SDL2 decodes the ."
         << SUPPORTED_EXTENSION << " files alone, so the " << sound->alias()
         << " sound needs the SDL_mixer library to be played");
    return false;
  }

  SDL_AudioSpec spec{};
  Uint8* buffer{nullptr};
  Uint32 length{0};

  if (SDL_LoadWAV(sound->filePath().c_str(), &spec, &buffer, &length) ==
      nullptr) {
    LOGE("Fail to read the " << sound->filePath()
                             << " sound file: " << SDL_GetError());
    return false;
  }

  const auto device = SDL_OpenAudioDevice(nullptr, 0, &spec, nullptr, 0);

  if (device == 0) {
    LOGE("Fail to open an audio device for the "
         << sound->alias() << " sound: " << SDL_GetError());
    SDL_FreeWAV(buffer);
    return false;
  }

  const auto queued = SDL_QueueAudio(device, buffer, length) == 0;

  SDL_FreeWAV(buffer);

  if (!queued) {
    LOGE("Fail to queue the " << sound->alias()
                              << " sound: " << SDL_GetError());
    SDL_CloseAudioDevice(device);
    return false;
  }

  SDL_PauseAudioDevice(device, 0);

  int waited{0};

  while (SDL_GetQueuedAudioSize(device) > 0 && waited < DRAIN_LIMIT_MS) {
    SDL_Delay(DRAIN_STEP_MS);
    waited += DRAIN_STEP_MS;
  }

  const auto played = SDL_GetQueuedAudioSize(device) == 0;

  SDL_CloseAudioDevice(device);

  if (!played) {
    LOGW("The " << sound->alias() << " sound was still playing after "
                << DRAIN_LIMIT_MS << " ms and has been cut");
  }

  return played;
}

IOpenGameArtSoundPlayerPtr OpenGameArtSdlSoundPlayer::create()
{
  return std::make_shared<OpenGameArtSdlSoundPlayer>();
}

}  // namespace opengameartaudio
