#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDGENERATEDSOUNDS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDGENERATEDSOUNDS_CLASS_H

#include <map>
#include <string>
#include <vector>

namespace freesoundaudio
{

/**
 * @brief A handful of sound paths standing in for the index the CMake freesound
 * audio enabler generates out of the real categories, so the tests stay
 * independent of the categories the machine running them happens to carry.
 */
class FreesoundGeneratedSounds
{
 public:
  using NamesList = std::vector<std::string>;

  inline static const std::map<std::string, NamesList> MOCKED_NAMES = {
      {"impact-sounds", {"Audio/impactMetal_light_000.wav"}},
      {"interface-sounds",
       {"Audio/click_001.ogg", "Audio/confirmation_001.wav"}},
  };

  static const NamesList& categories()
  {
    static const NamesList categoryNames = []() {
      NamesList collected;

      collected.reserve(MOCKED_NAMES.size());

      for (const auto& category : MOCKED_NAMES) {
        collected.push_back(category.first);
      }

      return collected;
    }();

    return categoryNames;
  }

  inline static const std::map<std::string, std::string> MOCKED_LICENSES = {
      {"impact-sounds/Audio/impactMetal_light_000.wav", "CC-BY-4.0"},
      {"interface-sounds/Audio/click_001.ogg", "CC0-1.0"},
      {"interface-sounds/Audio/confirmation_001.wav", "CC0-1.0"},
  };

  inline static const std::map<std::string, std::string> MOCKED_SOURCES = {
      {"impact-sounds/Audio/impactMetal_light_000.wav",
       "https://freesound.org/s/000000/"},
      {"interface-sounds/Audio/click_001.ogg",
       "https://freesound.org/s/111111/"},
      {"interface-sounds/Audio/confirmation_001.wav",
       "https://freesound.org/s/222222/"},
  };

  static const std::string& license(const std::string& soundAlias)
  {
    return recorded(MOCKED_LICENSES, soundAlias);
  }

  static const std::string& sourceUrl(const std::string& soundAlias)
  {
    return recorded(MOCKED_SOURCES, soundAlias);
  }

  static const NamesList& names(const std::string& categoryName)
  {
    static const NamesList noNames;

    const auto found = MOCKED_NAMES.find(categoryName);

    if (found == MOCKED_NAMES.cend()) {
      return noNames;
    }

    return found->second;
  }

 private:
  static const std::string& recorded(
      const std::map<std::string, std::string>& from,
      const std::string& soundAlias)
  {
    static const std::string none;

    const auto found = from.find(soundAlias);

    if (found == from.cend()) {
      return none;
    }

    return found->second;
  }
};

}  // namespace freesoundaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDGENERATEDSOUNDS_CLASS_H
