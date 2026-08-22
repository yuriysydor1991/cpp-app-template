#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IFONTAWESOMESTYLES_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IFONTAWESOMESTYLES_CLASS_H

#include <memory>
#include <string>
#include <vector>

#include "src/fontawesome/styles/IFontAwesomeStyle.h"

namespace fontawesome
{

/**
 * @brief The registry of the styles the Font Awesome Free distribution ships.
 *
 * Keeps the calling code away from instantiating the style descendants by
 * itself, so a style added to (or dropped from) the distribution stays a
 * matter of the registry alone.
 */
class IFontAwesomeStyles
{
 public:
  using IFontAwesomeStylesPtr = std::shared_ptr<IFontAwesomeStyles>;
  using StylesList = std::vector<IFontAwesomeStylePtr>;

  virtual ~IFontAwesomeStyles() = default;

  /**
   * @brief Gives every style of the distribution.
   *
   * @return Returns the styles list, never an empty one.
   */
  virtual const StylesList& all() const = 0;

  /**
   * @brief Searches for the style carrying the given name.
   *
   * @param styleName The style name of interest, the "solid" one for example.
   *
   * @return Returns the style instance or a nullptr one when the distribution
   * ships no style of such a name.
   */
  virtual IFontAwesomeStylePtr byName(const std::string& styleName) const = 0;
};

using IFontAwesomeStylesPtr = IFontAwesomeStyles::IFontAwesomeStylesPtr;

}  // namespace fontawesome

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IFONTAWESOMESTYLES_CLASS_H
