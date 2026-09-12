#include "src/freesoundaudio/player/FreesoundSdlMixerSoundPlayer.h"

#include <SDL.h>
#include <SDL_mixer.h>

#include <cassert>
#include <map>
#include <memory>
#include <string>

#include "src/freesoundaudio/FreesoundSound.h"
#include "src/freesoundaudio/player/IFreesoundSoundPlayer.h"
#include "src/log/log.h"

namespace freesoundaudio
{

namespace
{

// The sound file extensions the player answers for, each together with the
// Mix_Init flag of the decoder it asks SDL_mixer for. The RIFF/WAVE one asks
// for none at all: SDL_mixer reads those through SDL2 itself.
const std::map<std::string, int> DECODERS = {
    {"wav", 0},
    {"ogg", MIX_INIT_OGG},
    {"mp3", MIX_INIT_MP3},
    {"flac", MIX_INIT_FLAC},
};

int decodersOfInterest()
{
  int wanted{0};

  for (const auto& [extension, decoder] : DECODERS) {
    wanted |= decoder;
  }

  return wanted;
}

}  // namespace

FreesoundSdlMixerSoundPlayer::FreesoundSdlMixerSoundPlayer()
{
  if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
    LOGE("Fail to bring the SDL2 audio subsystem up: " << SDL_GetError());
    return;
  }

  mdecoders = Mix_Init(decodersOfInterest());

  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
                    MIX_DEFAULT_CHANNELS, CHUNK_SAMPLES) != 0) {
    LOGE("Fail to open the mixing audio device: " << Mix_GetError());
    Mix_Quit();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    return;
  }

  minitialized = true;

  LOGD("The SDL2 audio driver in use: " << SDL_GetCurrentAudioDriver());
}

FreesoundSdlMixerSoundPlayer::~FreesoundSdlMixerSoundPlayer()
{
  if (minitialized) {
    Mix_CloseAudio();
    Mix_Quit();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
  }
}

bool FreesoundSdlMixerSoundPlayer::supports(const std::string& extension) const
{
  const auto decoder = DECODERS.find(extension);

  if (!minitialized || decoder == DECODERS.end()) {
    return false;
  }

  return (decoder->second & mdecoders) == decoder->second;
}

bool FreesoundSdlMixerSoundPlayer::play(const FreesoundSoundPtr& sound)
{
  assert(sound != nullptr);

  if (sound == nullptr) {
    LOGE("No sound to play");
    return false;
  }

  if (!minitialized) {
    LOGE("No mixing audio device to play the " << sound->alias()
                                               << " sound with");
    return false;
  }

  if (!supports(sound->extension())) {
    LOGW("The SDL_mixer library at hand carries no ."
         << sound->extension() << " decoder, so the " << sound->alias()
         << " sound stays unplayable");
    return false;
  }

  auto* chunk = Mix_LoadWAV(sound->filePath().c_str());

  if (chunk == nullptr) {
    LOGE("Fail to decode the " << sound->filePath()
                               << " sound file: " << Mix_GetError());
    return false;
  }

  const auto channel = Mix_PlayChannel(-1, chunk, 0);

  if (channel < 0) {
    LOGE("Fail to play the " << sound->alias() << " sound: " << Mix_GetError());
    Mix_FreeChunk(chunk);
    return false;
  }

  int waited{0};

  while (Mix_Playing(channel) != 0 && waited < DRAIN_LIMIT_MS) {
    SDL_Delay(DRAIN_STEP_MS);
    waited += DRAIN_STEP_MS;
  }

  const auto played = Mix_Playing(channel) == 0;

  if (!played) {
    LOGW("The " << sound->alias() << " sound was still playing after "
                << DRAIN_LIMIT_MS << " ms and has been cut");
    Mix_HaltChannel(channel);
  }

  Mix_FreeChunk(chunk);

  return played;
}

IFreesoundSoundPlayerPtr FreesoundSdlMixerSoundPlayer::create()
{
  return std::make_shared<FreesoundSdlMixerSoundPlayer>();
}

}  // namespace freesoundaudio
