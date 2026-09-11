#include "src/opengameartaudio/sounds/OpenGameArtGeneratedSounds.h"

#include <map>
#include <string>

namespace opengameartaudio
{

namespace
{

// The stand-in of the index the opengameart audio enabler generates, so the
// unit tests below answer for the classes reading it and not for the packs the
// machine running them happens to carry.
const std::map<std::string, OpenGameArtGeneratedSounds::NamesList>& generated()
{
  static const std::map<std::string, OpenGameArtGeneratedSounds::NamesList>
      sounds{
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

const std::map<std::string, std::string>& generatedLicenses()
{
  static const std::map<std::string, std::string> licenses{
      {"impact-sounds", "CC-BY-3.0"},
      {"interface-sounds", "CC0-1.0"},
  };

  return licenses;
}

}  // namespace

const OpenGameArtGeneratedSounds::NamesList& OpenGameArtGeneratedSounds::packs()
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

const OpenGameArtGeneratedSounds::NamesList& OpenGameArtGeneratedSounds::names(
    const std::string& packName)
{
  static const NamesList none;

  const auto found = generated().find(packName);

  if (found == generated().cend()) {
    return none;
  }

  return found->second;
}

const std::string& OpenGameArtGeneratedSounds::license(
    const std::string& packName)
{
  static const std::string none;

  const auto found = generatedLicenses().find(packName);

  if (found == generatedLicenses().cend()) {
    return none;
  }

  return found->second;
}

}  // namespace opengameartaudio
