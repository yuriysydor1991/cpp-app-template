#include "src/kenneyaudio/sounds/KenneyGeneratedSounds.h"

#include <map>
#include <string>

namespace kenneyaudio
{

namespace
{

// The stand-in of the index the kenney audio enabler generates, so the unit
// tests below answer for the classes reading it and not for the packs the
// machine running them happens to carry.
const std::map<std::string, KenneyGeneratedSounds::NamesList>& generated()
{
  static const std::map<std::string, KenneyGeneratedSounds::NamesList> sounds{
      {"impact-sounds",
       {
           "Audio/impactMetal_light_000.ogg",
       }},
      {"interface-sounds",
       {
           "Audio/click_001.ogg",
           "Audio/confirmation_001.ogg",
       }},
  };

  return sounds;
}

}  // namespace

const KenneyGeneratedSounds::NamesList& KenneyGeneratedSounds::packs()
{
  static const NamesList packNames = []() {
    NamesList collected;

    collected.reserve(generated().size());

    for (const auto& pack : generated()) {
      collected.push_back(pack.first);
    }

    return collected;
  }();

  return packNames;
}

const KenneyGeneratedSounds::NamesList& KenneyGeneratedSounds::names(
    const std::string& packName)
{
  static const NamesList none;

  const auto found = generated().find(packName);

  if (found == generated().cend()) {
    return none;
  }

  return found->second;
}

}  // namespace kenneyaudio
