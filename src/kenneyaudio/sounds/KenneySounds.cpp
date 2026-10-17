#include "src/kenneyaudio/sounds/KenneySounds.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
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

    const auto& soundPaths = KenneyGeneratedSounds::names(packName);

    std::transform(soundPaths.cbegin(), soundPaths.cend(),
                   std::back_inserter(msounds), [&pack](const auto& soundPath) {
                     return KenneySound::create(pack, soundPath);
                   });
  }
}

const KenneySounds::SoundsList& KenneySounds::all() const { return msounds; }

KenneySounds::SoundsList KenneySounds::ofPack(const std::string& packName) const
{
  SoundsList found;

  std::copy_if(msounds.cbegin(), msounds.cend(), std::back_inserter(found),
               [&packName](const auto& sound) {
                 return sound->pack()->name() == packName;
               });

  return found;
}

KenneySoundPtr KenneySounds::find(const std::string& packName,
                                  const std::string& soundPath) const
{
  const auto found = std::find_if(msounds.cbegin(), msounds.cend(),
                                  [&packName, &soundPath](const auto& sound) {
                                    return sound->pack()->name() == packName &&
                                           sound->path() == soundPath;
                                  });

  return found == msounds.cend() ? KenneySoundPtr{} : *found;
}

KenneySounds::SoundsList KenneySounds::search(const std::string& namePart) const
{
  SoundsList found;

  std::copy_if(msounds.cbegin(), msounds.cend(), std::back_inserter(found),
               [&namePart](const auto& sound) {
                 return sound->name().find(namePart) != std::string::npos;
               });

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
