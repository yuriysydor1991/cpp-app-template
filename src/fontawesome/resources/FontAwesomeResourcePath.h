#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMERESOURCEPATH_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMERESOURCEPATH_CLASS_H

#include <string>

#include "src/fontawesome/FontAwesomeIcon.h"
#include "src/fontawesome/resources/IFontAwesomeResourcePath.h"

namespace fontawesome
{

/**
 * @brief The prefix handling every resource system locator shares.
 *
 * Keeps the given prefix in the single leading slash and no trailing slash
 * form, so the descendants concatenate it with an icon alias and nothing else.
 */
class FontAwesomeResourcePath : public IFontAwesomeResourcePath
{
 public:
  /**
   * @brief Constructs the locator placing the icons under the given prefix.
   *
   * @param gprefix The resource system prefix of the manifest in use.
   */
  explicit FontAwesomeResourcePath(std::string gprefix);

  const std::string& prefix() const override;

 protected:
  /**
   * @brief Gives the prefixed alias of the given icon, which every resource
   * system path of that icon is built upon.
   *
   * @param icon The icon of interest.
   *
   * @return Returns the "<prefix>/<style>/<name>.svg" path, an empty string
   * for a nullptr icon.
   */
  std::string prefixedAlias(const FontAwesomeIconPtr& icon) const;

 private:
  /**
   * @brief Brings the given prefix to the single leading slash and no trailing
   * slash form.
   *
   * @param gprefix The prefix to normalize.
   *
   * @return Returns the normalized prefix.
   */
  static std::string normalized(std::string gprefix);

  std::string mprefix;
};

}  // namespace fontawesome

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMERESOURCEPATH_CLASS_H
