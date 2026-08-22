#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEICONS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEICONS_CLASS_H

#include <cstddef>
#include <string>

#include "src/fontawesome/FontAwesomeIcon.h"
#include "src/fontawesome/icons/IFontAwesomeIcons.h"
#include "src/fontawesome/styles/IFontAwesomeStyles.h"

namespace fontawesome
{

/**
 * @brief The whole icon set gathered out of the generated icon names index and
 * the styles registry.
 */
class FontAwesomeIcons : public IFontAwesomeIcons
{
 public:
  /**
   * @brief Gathers the icons of every style the given registry holds.
   *
   * @param gstyles The styles registry to gather the icons of.
   */
  explicit FontAwesomeIcons(IFontAwesomeStylesPtr gstyles);

  const IconsList& all() const override;

  IconsList ofStyle(const std::string& styleName) const override;

  FontAwesomeIconPtr find(const std::string& styleName,
                          const std::string& iconName) const override;

  IconsList search(const std::string& namePart) const override;

  std::size_t count() const override;

  static IFontAwesomeIconsPtr create();

 private:
  /**
   * @brief Fills the icons list out of the generated icon names index.
   */
  void gather();

  IFontAwesomeStylesPtr mstyles;
  IconsList micons;
};

}  // namespace fontawesome

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEICONS_CLASS_H
