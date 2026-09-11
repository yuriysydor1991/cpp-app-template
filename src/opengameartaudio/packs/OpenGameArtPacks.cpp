#include "src/opengameartaudio/packs/OpenGameArtPacks.h"

#include <cstddef>
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

  for (const auto& packName : packNames) {
    mpacks.push_back(OpenGameArtPack::create(
        packName, OpenGameArtGeneratedSounds::license(packName)));
  }
}

const OpenGameArtPacks::PacksList& OpenGameArtPacks::all() const
{
  return mpacks;
}

IOpenGameArtPackPtr OpenGameArtPacks::find(const std::string& packName) const
{
  for (const auto& pack : mpacks) {
    if (pack->name() == packName) {
      return pack;
    }
  }

  return {};
}

std::size_t OpenGameArtPacks::count() const { return mpacks.size(); }

IOpenGameArtPacksPtr OpenGameArtPacks::create()
{
  return std::make_shared<OpenGameArtPacks>();
}

}  // namespace opengameartaudio
