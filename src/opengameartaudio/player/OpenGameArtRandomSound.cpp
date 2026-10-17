#include "src/opengameartaudio/player/OpenGameArtRandomSound.h"

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <random>
#include <string>

#include "src/log/log.h"
#include "src/opengameartaudio/OpenGameArtSound.h"
#include "src/opengameartaudio/sounds/IOpenGameArtSounds.h"

namespace opengameartaudio
{

OpenGameArtRandomSound::OpenGameArtRandomSound()
    : mgenerator{std::random_device{}()}
{
}

OpenGameArtRandomSound::OpenGameArtRandomSound(Seed gseed) : mgenerator{gseed}
{
}

OpenGameArtSoundPtr OpenGameArtRandomSound::pick(
    const IOpenGameArtSoundsPtr& sounds)
{
  if (sounds == nullptr) {
    LOGW("No sounds to draw one of");
    return {};
  }

  return pick(sounds->all());
}

OpenGameArtSoundPtr OpenGameArtRandomSound::pick(
    const IOpenGameArtSounds::SoundsList& sounds)
{
  if (sounds.empty()) {
    LOGW("No sounds to draw one of");
    return {};
  }

  std::uniform_int_distribution<std::size_t> drawn{0, sounds.size() - 1};

  return sounds.at(drawn(mgenerator));
}

OpenGameArtSoundPtr OpenGameArtRandomSound::pick(
    const IOpenGameArtSoundsPtr& sounds, const std::string& extension)
{
  if (sounds == nullptr) {
    LOGW("No sounds to draw one of");
    return {};
  }

  IOpenGameArtSounds::SoundsList ofExtension;

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

}  // namespace opengameartaudio
