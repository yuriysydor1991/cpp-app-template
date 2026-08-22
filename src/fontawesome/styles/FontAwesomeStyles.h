#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMESTYLES_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMESTYLES_CLASS_H

#include <string>

#include "src/fontawesome/styles/IFontAwesomeStyle.h"
#include "src/fontawesome/styles/IFontAwesomeStyles.h"

namespace fontawesome
{

/**
 * @brief The registry of the three styles the Font Awesome Free distribution
 * ships: the solid, the regular and the brands one.
 */
class FontAwesomeStyles : public IFontAwesomeStyles
{
 public:
  FontAwesomeStyles();

  const StylesList& all() const override;

  IFontAwesomeStylePtr byName(const std::string& styleName) const override;

  static IFontAwesomeStylesPtr create();

 private:
  StylesList mstyles;
};

}  // namespace fontawesome

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMESTYLES_CLASS_H
