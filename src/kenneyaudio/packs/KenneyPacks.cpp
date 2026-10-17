#include "src/kenneyaudio/packs/KenneyPacks.h"

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <string>

#include "src/kenneyaudio/packs/IKenneyPack.h"
#include "src/kenneyaudio/packs/IKenneyPacks.h"
#include "src/kenneyaudio/packs/KenneyPack.h"
#include "src/kenneyaudio/sounds/KenneyGeneratedSounds.h"

namespace kenneyaudio
{

KenneyPacks::KenneyPacks()
{
  const auto& packNames = KenneyGeneratedSounds::packs();

  mpacks.reserve(packNames.size());

  std::transform(
      packNames.cbegin(), packNames.cend(), std::back_inserter(mpacks),
      [](const auto& packName) { return KenneyPack::create(packName); });
}

const KenneyPacks::PacksList& KenneyPacks::all() const { return mpacks; }

IKenneyPackPtr KenneyPacks::find(const std::string& packName) const
{
  const auto found = std::find_if(
      mpacks.cbegin(), mpacks.cend(),
      [&packName](const auto& pack) { return pack->name() == packName; });

  return found == mpacks.cend() ? IKenneyPackPtr{} : *found;
}

std::size_t KenneyPacks::count() const { return mpacks.size(); }

IKenneyPacksPtr KenneyPacks::create()
{
  return std::make_shared<KenneyPacks>();
}

}  // namespace kenneyaudio
