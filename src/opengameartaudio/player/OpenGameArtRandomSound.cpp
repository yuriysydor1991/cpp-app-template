#include "src/opengameartaudio/player/OpenGameArtRandomSound.h"

#include <cstddef>
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
  if (sounds == nullptr || sounds->all().empty()) {
    LOGW("No sounds to draw one of");
    return {};
  }

  std::uniform_int_distribution<std::size_t> drawn{0, sounds->all().size() - 1};

  return sounds->all().at(drawn(mgenerator));
}

OpenGameArtSoundPtr OpenGameArtRandomSound::pick(
    const IOpenGameArtSoundsPtr& sounds, const std::string& extension)
{
  if (sounds == nullptr) {
    LOGW("No sounds to draw one of");
    return {};
  }

  IOpenGameArtSounds::SoundsList ofExtension;

  for (const auto& sound : sounds->all()) {
    if (sound->extension() == extension) {
      ofExtension.push_back(sound);
    }
  }

  if (ofExtension.empty()) {
    LOGW("No ." << extension << " sound among the " << sounds->count()
                << " available ones");
    return {};
  }

  std::uniform_int_distribution<std::size_t> drawn{0, ofExtension.size() - 1};

  return ofExtension.at(drawn(mgenerator));
}

}  // namespace opengameartaudio
