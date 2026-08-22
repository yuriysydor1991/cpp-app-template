#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEBRANDSSTYLE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEBRANDSSTYLE_CLASS_H

#include <string>

#include "src/fontawesome/styles/IFontAwesomeStyle.h"

namespace fontawesome
{

/**
 * @brief The Font Awesome Free "brands" style: the third party company and
 * product logotypes style.
 */
class FontAwesomeBrandsStyle : public IFontAwesomeStyle
{
 public:
  std::string name() const override;

  std::string webfontFileName() const override;

  static IFontAwesomeStylePtr create();
};

}  // namespace fontawesome

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEBRANDSSTYLE_CLASS_H
