#include "src/freesoundaudio/sounds/FreesoundGeneratedSounds.h"

#include <algorithm>
#include <iterator>
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
               "Audio/impactMetal_light_000.wav",
           }},
          {"interface-sounds",
           {
               "Audio/click_001.ogg",
               "Audio/confirmation_001.wav",
           }},
      };

  return sounds;
}

// Freesound licenses a sound rather than a collection, so both the license and
// the page it came from are keyed by the single sound alias.
const std::map<std::string, std::string>& generatedLicenses()
{
  static const std::map<std::string, std::string> licenses{
      {"impact-sounds/Audio/impactMetal_light_000.wav", "CC-BY-4.0"},
      {"interface-sounds/Audio/click_001.ogg", "CC0-1.0"},
      {"interface-sounds/Audio/confirmation_001.wav", "CC0-1.0"},
  };

  return licenses;
}

const std::map<std::string, std::string>& generatedSources()
{
  static const std::map<std::string, std::string> sources{
      {"impact-sounds/Audio/impactMetal_light_000.wav",
       "https://cdn.freesound.org/previews/000/000000_0-hq.ogg"},
      {"interface-sounds/Audio/click_001.ogg",
       "https://cdn.freesound.org/previews/111/111111_1-hq.ogg"},
      {"interface-sounds/Audio/confirmation_001.wav",
       "https://cdn.freesound.org/previews/222/222222_2-hq.ogg"},
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

    std::transform(generated().cbegin(), generated().cend(),
                   std::back_inserter(collected),
                   [](const auto& category) { return category.first; });

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
