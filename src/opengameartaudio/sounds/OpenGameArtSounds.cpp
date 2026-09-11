#include "src/opengameartaudio/sounds/OpenGameArtSounds.h"

#include <cassert>
#include <cstddef>
#include <memory>
#include <string>
#include <utility>

#include "src/log/log.h"
#include "src/opengameartaudio/OpenGameArtSound.h"
#include "src/opengameartaudio/packs/IOpenGameArtPacks.h"
#include "src/opengameartaudio/packs/OpenGameArtPacks.h"
#include "src/opengameartaudio/sounds/IOpenGameArtSounds.h"
#include "src/opengameartaudio/sounds/OpenGameArtGeneratedSounds.h"

namespace opengameartaudio
{

OpenGameArtSounds::OpenGameArtSounds(IOpenGameArtPacksPtr gpacks)
{
  assert(gpacks != nullptr);

  if (gpacks == nullptr) {
    LOGE("No packs to gather the sounds of");
    return;
  }

  for (const auto& pack : gpacks->all()) {
    // The name is materialized because IOpenGameArtPack::name gives it by value
    // and the index answers with a reference into it's own storage.
    const auto packName = pack->name();

    for (const auto& soundPath : OpenGameArtGeneratedSounds::names(packName)) {
      msounds.push_back(OpenGameArtSound::create(pack, soundPath));
    }
  }
}

const OpenGameArtSounds::SoundsList& OpenGameArtSounds::all() const
{
  return msounds;
}

OpenGameArtSounds::SoundsList OpenGameArtSounds::ofPack(
    const std::string& packName) const
{
  SoundsList found;

  for (const auto& sound : msounds) {
    if (sound->pack()->name() == packName) {
      found.push_back(sound);
    }
  }

  return found;
}

OpenGameArtSoundPtr OpenGameArtSounds::find(const std::string& packName,
                                            const std::string& soundPath) const
{
  for (const auto& sound : msounds) {
    if (sound->pack()->name() == packName && sound->path() == soundPath) {
      return sound;
    }
  }

  return {};
}

OpenGameArtSounds::SoundsList OpenGameArtSounds::search(
    const std::string& namePart) const
{
  SoundsList found;

  for (const auto& sound : msounds) {
    if (sound->name().find(namePart) != std::string::npos) {
      found.push_back(sound);
    }
  }

  return found;
}

std::size_t OpenGameArtSounds::count() const { return msounds.size(); }

IOpenGameArtSoundsPtr OpenGameArtSounds::create()
{
  return create(OpenGameArtPacks::create());
}

IOpenGameArtSoundsPtr OpenGameArtSounds::create(IOpenGameArtPacksPtr gpacks)
{
  return std::make_shared<OpenGameArtSounds>(std::move(gpacks));
}

}  // namespace opengameartaudio
