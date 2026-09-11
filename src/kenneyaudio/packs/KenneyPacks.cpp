#include "src/kenneyaudio/packs/KenneyPacks.h"

#include <cstddef>
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

  for (const auto& packName : packNames) {
    mpacks.push_back(KenneyPack::create(packName));
  }
}

const KenneyPacks::PacksList& KenneyPacks::all() const { return mpacks; }

IKenneyPackPtr KenneyPacks::find(const std::string& packName) const
{
  for (const auto& pack : mpacks) {
    if (pack->name() == packName) {
      return pack;
    }
  }

  return {};
}

std::size_t KenneyPacks::count() const { return mpacks.size(); }

IKenneyPacksPtr KenneyPacks::create()
{
  return std::make_shared<KenneyPacks>();
}

}  // namespace kenneyaudio
