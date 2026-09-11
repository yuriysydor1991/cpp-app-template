#include "src/freesoundaudio/player/FreesoundRandomSound.h"

#include <cstddef>
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
  if (sounds == nullptr || sounds->all().empty()) {
    LOGW("No sounds to draw one of");
    return {};
  }

  std::uniform_int_distribution<std::size_t> drawn{0, sounds->all().size() - 1};

  return sounds->all().at(drawn(mgenerator));
}

FreesoundSoundPtr FreesoundRandomSound::pick(const IFreesoundSoundsPtr& sounds,
                                             const std::string& extension)
{
  if (sounds == nullptr) {
    LOGW("No sounds to draw one of");
    return {};
  }

  IFreesoundSounds::SoundsList ofExtension;

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

}  // namespace freesoundaudio
