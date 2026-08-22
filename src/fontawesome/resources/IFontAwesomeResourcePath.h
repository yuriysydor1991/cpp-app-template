#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IFONTAWESOMERESOURCEPATH_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IFONTAWESOMERESOURCEPATH_CLASS_H

#include <memory>
#include <string>

#include "src/fontawesome/FontAwesomeIcon.h"

namespace fontawesome
{

/**
 * @brief The run time locator of an icon embedded into the resource system of
 * a GUI toolkit.
 *
 * An icon compiled into a binary is no file any more, so every toolkit
 * resolves it by a path of it's own resource system. Every descendant answers
 * for one of those systems and keys the icon by the very alias the generated
 * resource manifest of that system carries.
 */
class IFontAwesomeResourcePath
{
 public:
  using IFontAwesomeResourcePathPtr = std::shared_ptr<IFontAwesomeResourcePath>;

  virtual ~IFontAwesomeResourcePath() = default;

  /**
   * @brief Gives the resource system prefix every icon path sits under.
   */
  virtual const std::string& prefix() const = 0;

  /**
   * @brief Gives the path the toolkit resolves the given icon by.
   *
   * @param icon The icon of interest.
   *
   * @return Returns the resource path, an empty string for a nullptr icon.
   */
  virtual std::string of(const FontAwesomeIconPtr& icon) const = 0;

  /**
   * @brief Gives the URI the toolkit resolves the given icon by, for the calls
   * taking an URI instead of a plain resource path.
   *
   * @param icon The icon of interest.
   *
   * @return Returns the resource URI, an empty string for a nullptr icon.
   */
  virtual std::string uriOf(const FontAwesomeIconPtr& icon) const = 0;
};

using IFontAwesomeResourcePathPtr =
    IFontAwesomeResourcePath::IFontAwesomeResourcePathPtr;

}  // namespace fontawesome

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IFONTAWESOMERESOURCEPATH_CLASS_H
