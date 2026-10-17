#include "src/opengameartaudio/packs/OpenGameArtPacks.h"

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <string>

#include "src/opengameartaudio/packs/IOpenGameArtPack.h"
#include "src/opengameartaudio/packs/IOpenGameArtPacks.h"
#include "src/opengameartaudio/packs/OpenGameArtPack.h"
#include "src/opengameartaudio/sounds/OpenGameArtGeneratedSounds.h"

namespace opengameartaudio
{

OpenGameArtPacks::OpenGameArtPacks()
{
  const auto& packNames = OpenGameArtGeneratedSounds::packs();

  mpacks.reserve(packNames.size());

  std::transform(packNames.cbegin(), packNames.cend(),
                 std::back_inserter(mpacks), [](const auto& packName) {
                   return OpenGameArtPack::create(
                       packName, OpenGameArtGeneratedSounds::license(packName));
                 });
}

const OpenGameArtPacks::PacksList& OpenGameArtPacks::all() const
{
  return mpacks;
}

IOpenGameArtPackPtr OpenGameArtPacks::find(const std::string& packName) const
{
  const auto found = std::find_if(
      mpacks.cbegin(), mpacks.cend(),
      [&packName](const auto& pack) { return pack->name() == packName; });

  return found == mpacks.cend() ? IOpenGameArtPackPtr{} : *found;
}

std::size_t OpenGameArtPacks::count() const { return mpacks.size(); }

IOpenGameArtPacksPtr OpenGameArtPacks::create()
{
  return std::make_shared<OpenGameArtPacks>();
}

}  // namespace opengameartaudio
