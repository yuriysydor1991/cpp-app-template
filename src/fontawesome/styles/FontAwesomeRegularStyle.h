#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEREGULARSTYLE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEREGULARSTYLE_CLASS_H

#include <string>

#include "src/fontawesome/styles/IFontAwesomeStyle.h"

namespace fontawesome
{

/**
 * @brief The Font Awesome Free "regular" style: the outlined shapes style.
 */
class FontAwesomeRegularStyle : public IFontAwesomeStyle
{
 public:
  std::string name() const override;

  std::string webfontFileName() const override;

  static IFontAwesomeStylePtr create();
};

}  // namespace fontawesome

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEREGULARSTYLE_CLASS_H
