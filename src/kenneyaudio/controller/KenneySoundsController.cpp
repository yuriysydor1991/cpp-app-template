#include "src/kenneyaudio/controller/KenneySoundsController.h"

#include <algorithm>
#include <cassert>
#include <iterator>
#include <memory>
#include <utility>

#include "src/kenneyaudio/KenneySound.h"
#include "src/kenneyaudio/controller/IKenneySoundsController.h"
#include "src/kenneyaudio/player/IKenneySoundPlayer.h"
#include "src/kenneyaudio/player/KenneySoundPlayerFactory.h"
#include "src/kenneyaudio/sounds/IKenneySounds.h"
#include "src/log/log.h"

namespace kenneyaudio
{

KenneySoundsController::KenneySoundsController(IKenneySoundsPtr gsounds,
                                               IKenneySoundPlayerPtr gplayer)
    : msounds{std::move(gsounds)}, mplayer{std::move(gplayer)}
{
  assert(msounds != nullptr);
}

bool KenneySoundsController::playable() const { return mplayer != nullptr; }

IKenneySounds::SoundsList KenneySoundsController::playableSounds() const
{
  IKenneySounds::SoundsList playableOnes;

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

KenneySoundPtr KenneySoundsController::draw()
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

bool KenneySoundsController::play(const KenneySoundPtr& sound)
{
  if (mplayer == nullptr) {
    LOGD("No audio backend is built in to play a sound with");
    return false;
  }

  return mplayer->play(sound);
}

IKenneySoundsControllerPtr KenneySoundsController::create(
    IKenneySoundsPtr gsounds)
{
  return create(std::move(gsounds), KenneySoundPlayerFactory::create());
}

IKenneySoundsControllerPtr KenneySoundsController::create(
    IKenneySoundsPtr gsounds, IKenneySoundPlayerPtr gplayer)
{
  return std::make_shared<KenneySoundsController>(std::move(gsounds),
                                                  std::move(gplayer));
}

}  // namespace kenneyaudio
