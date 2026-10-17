#include "src/freesoundaudio/player/FreesoundRandomSound.h"

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <random>
#include <string>

#include "src/freesoundaudio/FreesoundSound.h"
#include "src/freesoundaudio/sounds/IFreesoundSounds.h"
#include "src/log/log.h"

namespace freesoundaudio
{

FreesoundRandomSound::FreesoundRandomSound()
    : mgenerator{std::random_device{}()}
{
}

FreesoundRandomSound::FreesoundRandomSound(Seed gseed) : mgenerator{gseed} {}

FreesoundSoundPtr FreesoundRandomSound::pick(const IFreesoundSoundsPtr& sounds)
{
  if (sounds == nullptr) {
    LOGW("No sounds to draw one of");
    return {};
  }

  return pick(sounds->all());
}

FreesoundSoundPtr FreesoundRandomSound::pick(
    const IFreesoundSounds::SoundsList& sounds)
{
  if (sounds.empty()) {
    LOGW("No sounds to draw one of");
    return {};
  }

  std::uniform_int_distribution<std::size_t> drawn{0, sounds.size() - 1};

  return sounds.at(drawn(mgenerator));
}

FreesoundSoundPtr FreesoundRandomSound::pick(const IFreesoundSoundsPtr& sounds,
                                             const std::string& extension)
{
  if (sounds == nullptr) {
    LOGW("No sounds to draw one of");
    return {};
  }

  IFreesoundSounds::SoundsList ofExtension;

  const auto& all = sounds->all();

  std::copy_if(all.cbegin(), all.cend(), std::back_inserter(ofExtension),
               [&extension](const auto& sound) {
                 return sound->extension() == extension;
               });

  if (ofExtension.empty()) {
    LOGW("No ." << extension << " sound among the " << sounds->count()
                << " available ones");
    return {};
  }

  std::uniform_int_distribution<std::size_t> drawn{0, ofExtension.size() - 1};

  return ofExtension.at(drawn(mgenerator));
}

}  // namespace freesoundaudio
