#include "src/freesoundaudio/controller/FreesoundSoundsController.h"

#include <algorithm>
#include <cassert>
#include <iterator>
#include <memory>
#include <utility>

#include "src/freesoundaudio/FreesoundSound.h"
#include "src/freesoundaudio/controller/IFreesoundSoundsController.h"
#include "src/freesoundaudio/player/FreesoundSoundPlayerFactory.h"
#include "src/freesoundaudio/player/IFreesoundSoundPlayer.h"
#include "src/freesoundaudio/sounds/IFreesoundSounds.h"
#include "src/log/log.h"

namespace freesoundaudio
{

FreesoundSoundsController::FreesoundSoundsController(
    IFreesoundSoundsPtr gsounds, IFreesoundSoundPlayerPtr gplayer)
    : msounds{std::move(gsounds)}, mplayer{std::move(gplayer)}
{
  assert(msounds != nullptr);
}

bool FreesoundSoundsController::playable() const { return mplayer != nullptr; }

IFreesoundSounds::SoundsList FreesoundSoundsController::playableSounds() const
{
  IFreesoundSounds::SoundsList playableOnes;

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

FreesoundSoundPtr FreesoundSoundsController::draw()
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

bool FreesoundSoundsController::play(const FreesoundSoundPtr& sound)
{
  if (mplayer == nullptr) {
    LOGD("No audio backend is built in to play a sound with");
    return false;
  }

  return mplayer->play(sound);
}

IFreesoundSoundsControllerPtr FreesoundSoundsController::create(
    IFreesoundSoundsPtr gsounds)
{
  return create(std::move(gsounds), FreesoundSoundPlayerFactory::create());
}

IFreesoundSoundsControllerPtr FreesoundSoundsController::create(
    IFreesoundSoundsPtr gsounds, IFreesoundSoundPlayerPtr gplayer)
{
  return std::make_shared<FreesoundSoundsController>(std::move(gsounds),
                                                     std::move(gplayer));
}

}  // namespace freesoundaudio
