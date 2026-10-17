#include "src/opengameartaudio/controller/OpenGameArtSoundsController.h"

#include <algorithm>
#include <cassert>
#include <iterator>
#include <memory>
#include <utility>

#include "src/log/log.h"
#include "src/opengameartaudio/OpenGameArtSound.h"
#include "src/opengameartaudio/controller/IOpenGameArtSoundsController.h"
#include "src/opengameartaudio/player/IOpenGameArtSoundPlayer.h"
#include "src/opengameartaudio/player/OpenGameArtSoundPlayerFactory.h"
#include "src/opengameartaudio/sounds/IOpenGameArtSounds.h"

namespace opengameartaudio
{

OpenGameArtSoundsController::OpenGameArtSoundsController(
    IOpenGameArtSoundsPtr gsounds, IOpenGameArtSoundPlayerPtr gplayer)
    : msounds{std::move(gsounds)}, mplayer{std::move(gplayer)}
{
  assert(msounds != nullptr);
}

bool OpenGameArtSoundsController::playable() const
{
  return mplayer != nullptr;
}

IOpenGameArtSounds::SoundsList OpenGameArtSoundsController::playableSounds()
    const
{
  IOpenGameArtSounds::SoundsList playableOnes;

  if (msounds == nullptr || mplayer == nullptr) {
    return playableOnes;
  }

  const auto& all = msounds->all();

  std::copy_if(all.cbegin(), all.cend(), std::back_inserter(playableOnes),
               [this](const auto& sound) {
                 return mplayer->supports(sound->extension());
               });

  return playableOnes;
}

OpenGameArtSoundPtr OpenGameArtSoundsController::draw()
{
  if (msounds == nullptr) {
    LOGE("No sounds to draw one of");
    return {};
  }

  const auto playableOnes = playableSounds();

  if (!playableOnes.empty()) {
    return mdrawn.pick(playableOnes);
  }

  // Nothing the backend decodes, so the draw still gives a sound worth showing
  // instead of nothing at all.
  return mdrawn.pick(msounds);
}

bool OpenGameArtSoundsController::play(const OpenGameArtSoundPtr& sound)
{
  if (mplayer == nullptr) {
    LOGD("No audio backend is built in to play a sound with");
    return false;
  }

  return mplayer->play(sound);
}

IOpenGameArtSoundsControllerPtr OpenGameArtSoundsController::create(
    IOpenGameArtSoundsPtr gsounds)
{
  return create(std::move(gsounds), OpenGameArtSoundPlayerFactory::create());
}

IOpenGameArtSoundsControllerPtr OpenGameArtSoundsController::create(
    IOpenGameArtSoundsPtr gsounds, IOpenGameArtSoundPlayerPtr gplayer)
{
  return std::make_shared<OpenGameArtSoundsController>(std::move(gsounds),
                                                       std::move(gplayer));
}

}  // namespace opengameartaudio
