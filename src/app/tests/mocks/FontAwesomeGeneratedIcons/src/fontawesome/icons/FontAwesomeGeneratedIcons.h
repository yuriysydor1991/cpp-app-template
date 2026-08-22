#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEGENERATEDICONS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEGENERATEDICONS_CLASS_H

#include <map>
#include <string>
#include <vector>

namespace fontawesome
{

/**
 * @brief A handful of icon names standing in for the index the CMake
 * fontawesome enabler generates out of the real checkout, so the tests stay
 * independent of the Font Awesome release in use.
 */
class FontAwesomeGeneratedIcons
{
 public:
  using NamesList = std::vector<std::string>;

  inline static const std::map<std::string, NamesList> MOCKED_NAMES = {
      {"brands", {"github", "gitlab"}},
      {"regular", {"user"}},
      {"solid", {"folder-open", "gear", "magnifying-glass"}},
  };

  static const NamesList& names(const std::string& styleName)
  {
    static const NamesList noNames;

    const auto found = MOCKED_NAMES.find(styleName);

    if (found == MOCKED_NAMES.cend()) {
      return noNames;
    }

    return found->second;
  }
};

}  // namespace fontawesome

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEGENERATEDICONS_CLASS_H
