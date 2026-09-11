#include "src/kenneyaudio/player/KenneyRandomSound.h"

#include <cstddef>
#include <random>
#include <string>

#include "src/kenneyaudio/KenneySound.h"
#include "src/kenneyaudio/sounds/IKenneySounds.h"
#include "src/log/log.h"

namespace kenneyaudio
{

KenneyRandomSound::KenneyRandomSound() : mgenerator{std::random_device{}()} {}

KenneyRandomSound::KenneyRandomSound(Seed gseed) : mgenerator{gseed} {}

KenneySoundPtr KenneyRandomSound::pick(const IKenneySoundsPtr& sounds)
{
  if (sounds == nullptr || sounds->all().empty()) {
    LOGW("No sounds to draw one of");
    return {};
  }

  std::uniform_int_distribution<std::size_t> drawn{0, sounds->all().size() - 1};

  return sounds->all().at(drawn(mgenerator));
}

KenneySoundPtr KenneyRandomSound::pick(const IKenneySoundsPtr& sounds,
                                       const std::string& extension)
{
  if (sounds == nullptr) {
    LOGW("No sounds to draw one of");
    return {};
  }

  IKenneySounds::SoundsList ofExtension;

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

}  // namespace kenneyaudio
