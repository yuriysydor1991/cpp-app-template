#include "src/freesoundaudio/sounds/FreesoundGeneratedSounds.h"

#include <map>
#include <string>

namespace freesoundaudio
{

namespace
{

const std::map<std::string, FreesoundGeneratedSounds::NamesList>& generated()
{
  static const std::map<std::string, FreesoundGeneratedSounds::NamesList>
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

// Freesound licenses a sound rather than a collection, so both the license and
// the page it came from are keyed by the single sound alias.
const std::map<std::string, std::string>& generatedLicenses()
{
  static const std::map<std::string, std::string> licenses{
      {"impact-sounds/Audio/impactMetal_light_000.ogg", "CC-BY-4.0"},
      {"interface-sounds/Audio/click_001.ogg", "CC0-1.0"},
      {"interface-sounds/Audio/confirmation_001.ogg", "CC0-1.0"},
  };

  return licenses;
}

const std::map<std::string, std::string>& generatedSources()
{
  static const std::map<std::string, std::string> sources{
      {"impact-sounds/Audio/impactMetal_light_000.ogg",
       "https://freesound.org/s/000000/"},
      {"interface-sounds/Audio/click_001.ogg",
       "https://freesound.org/s/111111/"},
      {"interface-sounds/Audio/confirmation_001.ogg",
       "https://freesound.org/s/222222/"},
  };

  return sources;
}

const std::string& of(const std::map<std::string, std::string>& recorded,
                      const std::string& soundAlias)
{
  static const std::string none;

  const auto found = recorded.find(soundAlias);

  if (found == recorded.cend()) {
    return none;
  }

  return found->second;
}

}  // namespace

const FreesoundGeneratedSounds::NamesList&
FreesoundGeneratedSounds::categories()
{
  static const NamesList categoryNames = []() {
    NamesList collected;

    collected.reserve(generated().size());

    for (const auto& category : generated()) {
      collected.push_back(category.first);
    }

    return collected;
  }();

  return categoryNames;
}

const FreesoundGeneratedSounds::NamesList& FreesoundGeneratedSounds::names(
    const std::string& categoryName)
{
  static const NamesList none;

  const auto found = generated().find(categoryName);

  if (found == generated().cend()) {
    return none;
  }

  return found->second;
}

const std::string& FreesoundGeneratedSounds::license(
    const std::string& soundAlias)
{
  return of(generatedLicenses(), soundAlias);
}

const std::string& FreesoundGeneratedSounds::sourceUrl(
    const std::string& soundAlias)
{
  return of(generatedSources(), soundAlias);
}

}  // namespace freesoundaudio
