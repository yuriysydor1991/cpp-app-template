#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IFONTAWESOMEICONS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IFONTAWESOMEICONS_CLASS_H

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "src/fontawesome/FontAwesomeIcon.h"

namespace fontawesome
{

/**
 * @brief The whole icon set of the Font Awesome checkout the project has been
 * configured with.
 *
 * Every icon of every enabled style is reachable here, so the application code
 * picks the ones it needs (and hands them over to the resource system of it's
 * GUI toolkit) without a single icon name written into the sources by hand.
 */
class IFontAwesomeIcons
{
 public:
  using IFontAwesomeIconsPtr = std::shared_ptr<IFontAwesomeIcons>;
  using IconsList = std::vector<FontAwesomeIconPtr>;

  virtual ~IFontAwesomeIcons() = default;

  /**
   * @brief Gives every icon of every style, ordered by the style and then by
   * the icon name.
   *
   * @return Returns the whole icon set.
   */
  virtual const IconsList& all() const = 0;

  /**
   * @brief Gives every icon of the given style.
   *
   * @param styleName The style name of interest, the "solid" one for example.
   *
   * @return Returns the icons of the style, an empty list when the set carries
   * no such style.
   */
  virtual IconsList ofStyle(const std::string& styleName) const = 0;

  /**
   * @brief Searches for the icon of the given style and name.
   *
   * @param styleName The style name of interest, the "solid" one for example.
   * @param iconName The plain icon name with no style, path or extension
   * parts, the "folder-open" one for example.
   *
   * @return Returns the icon or a nullptr one when the set carries none.
   */
  virtual FontAwesomeIconPtr find(const std::string& styleName,
                                  const std::string& iconName) const = 0;

  /**
   * @brief Gives every icon which name contains the given part.
   *
   * The counterpart of a "find the icons of interest by hand" browse over the
   * checkout, so no browser and no icon gallery page is needed to look one up.
   *
   * @param namePart The icon name part to look for, the "arrow" one for
   * example.
   *
   * @return Returns the matching icons of every style.
   */
  virtual IconsList search(const std::string& namePart) const = 0;

  /**
   * @brief Gives the count of the icons the whole set carries.
   */
  virtual std::size_t count() const = 0;
};

using IFontAwesomeIconsPtr = IFontAwesomeIcons::IFontAwesomeIconsPtr;

}  // namespace fontawesome

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IFONTAWESOMEICONS_CLASS_H
