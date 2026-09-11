#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTGENERATEDSOUNDS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTGENERATEDSOUNDS_CLASS_H

#include <map>
#include <string>
#include <vector>

namespace opengameartaudio
{

/**
 * @brief A handful of sound paths standing in for the index the CMake
 * opengameart audio enabler generates out of the real packs, so the tests stay
 * independent of the packs the machine running them happens to carry.
 */
class OpenGameArtGeneratedSounds
{
 public:
  using NamesList = std::vector<std::string>;

  inline static const std::map<std::string, NamesList> MOCKED_NAMES = {
      {"impact-sounds", {"Audio/impactMetal_light_000.wav"}},
      {"interface-sounds",
       {"Audio/click_001.ogg", "Audio/confirmation_001.wav"}},
  };

  static const NamesList& packs()
  {
    static const NamesList packNames = []() {
      NamesList collected;

      collected.reserve(MOCKED_NAMES.size());

      for (const auto& pack : MOCKED_NAMES) {
        collected.push_back(pack.first);
      }

      return collected;
    }();

    return packNames;
  }

  inline static const std::map<std::string, std::string> MOCKED_LICENSES = {
      {"impact-sounds", "CC-BY-3.0"},
      {"interface-sounds", "CC0-1.0"},
  };

  static const std::string& license(const std::string& packName)
  {
    static const std::string none;

    const auto found = MOCKED_LICENSES.find(packName);

    if (found == MOCKED_LICENSES.cend()) {
      return none;
    }

    return found->second;
  }

  static const NamesList& names(const std::string& packName)
  {
    static const NamesList noNames;

    const auto found = MOCKED_NAMES.find(packName);

    if (found == MOCKED_NAMES.cend()) {
      return noNames;
    }

    return found->second;
  }
};

}  // namespace opengameartaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTGENERATEDSOUNDS_CLASS_H
