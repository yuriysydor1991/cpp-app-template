#include "src/opengameartaudio/sounds/OpenGameArtSounds.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
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

    const auto& soundPaths = OpenGameArtGeneratedSounds::names(packName);

    std::transform(soundPaths.cbegin(), soundPaths.cend(),
                   std::back_inserter(msounds), [&pack](const auto& soundPath) {
                     return OpenGameArtSound::create(pack, soundPath);
                   });
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

  std::copy_if(msounds.cbegin(), msounds.cend(), std::back_inserter(found),
               [&packName](const auto& sound) {
                 return sound->pack()->name() == packName;
               });

  return found;
}

OpenGameArtSoundPtr OpenGameArtSounds::find(const std::string& packName,
                                            const std::string& soundPath) const
{
  const auto found = std::find_if(msounds.cbegin(), msounds.cend(),
                                  [&packName, &soundPath](const auto& sound) {
                                    return sound->pack()->name() == packName &&
                                           sound->path() == soundPath;
                                  });

  return found == msounds.cend() ? OpenGameArtSoundPtr{} : *found;
}

OpenGameArtSounds::SoundsList OpenGameArtSounds::search(
    const std::string& namePart) const
{
  SoundsList found;

  std::copy_if(msounds.cbegin(), msounds.cend(), std::back_inserter(found),
               [&namePart](const auto& sound) {
                 return sound->name().find(namePart) != std::string::npos;
               });

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
