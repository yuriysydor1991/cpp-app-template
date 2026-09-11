#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYGENERATEDSOUNDS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYGENERATEDSOUNDS_CLASS_H

#include <map>
#include <string>
#include <vector>

namespace kenneyaudio
{

/**
 * @brief A handful of sound paths standing in for the index the CMake kenney
 * audio enabler generates out of the real packs, so the tests stay independent
 * of the packs the machine running them happens to carry.
 */
class KenneyGeneratedSounds
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

}  // namespace kenneyaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_KENNEYGENERATEDSOUNDS_CLASS_H
