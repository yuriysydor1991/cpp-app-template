#include "src/kenneyaudio/sounds/KenneySounds.h"

#include <cassert>
#include <cstddef>
#include <memory>
#include <string>
#include <utility>

#include "src/kenneyaudio/KenneySound.h"
#include "src/kenneyaudio/packs/IKenneyPacks.h"
#include "src/kenneyaudio/packs/KenneyPacks.h"
#include "src/kenneyaudio/sounds/IKenneySounds.h"
#include "src/kenneyaudio/sounds/KenneyGeneratedSounds.h"
#include "src/log/log.h"

namespace kenneyaudio
{

KenneySounds::KenneySounds(IKenneyPacksPtr gpacks)
{
  assert(gpacks != nullptr);

  if (gpacks == nullptr) {
    LOGE("No packs to gather the sounds of");
    return;
  }

  for (const auto& pack : gpacks->all()) {
    // The name is materialized because IKenneyPack::name gives it by value and
    // the index answers with a reference into it's own storage.
    const auto packName = pack->name();

    for (const auto& soundPath : KenneyGeneratedSounds::names(packName)) {
      msounds.push_back(KenneySound::create(pack, soundPath));
    }
  }
}

const KenneySounds::SoundsList& KenneySounds::all() const { return msounds; }

KenneySounds::SoundsList KenneySounds::ofPack(const std::string& packName) const
{
  SoundsList found;

  for (const auto& sound : msounds) {
    if (sound->pack()->name() == packName) {
      found.push_back(sound);
    }
  }

  return found;
}

KenneySoundPtr KenneySounds::find(const std::string& packName,
                                  const std::string& soundPath) const
{
  for (const auto& sound : msounds) {
    if (sound->pack()->name() == packName && sound->path() == soundPath) {
      return sound;
    }
  }

  return {};
}

KenneySounds::SoundsList KenneySounds::search(const std::string& namePart) const
{
  SoundsList found;

  for (const auto& sound : msounds) {
    if (sound->name().find(namePart) != std::string::npos) {
      found.push_back(sound);
    }
  }

  return found;
}

std::size_t KenneySounds::count() const { return msounds.size(); }

IKenneySoundsPtr KenneySounds::create()
{
  return create(KenneyPacks::create());
}

IKenneySoundsPtr KenneySounds::create(IKenneyPacksPtr gpacks)
{
  return std::make_shared<KenneySounds>(std::move(gpacks));
}

}  // namespace kenneyaudio
