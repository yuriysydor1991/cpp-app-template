#include "src/fontawesome/styles/FontAwesomeStyles.h"

#include <algorithm>
#include <memory>
#include <string>

#include "src/fontawesome/styles/FontAwesomeBrandsStyle.h"
#include "src/fontawesome/styles/FontAwesomeRegularStyle.h"
#include "src/fontawesome/styles/FontAwesomeSolidStyle.h"
#include "src/fontawesome/styles/IFontAwesomeStyle.h"
#include "src/fontawesome/styles/IFontAwesomeStyles.h"
#include "src/log/log.h"

namespace fontawesome
{

FontAwesomeStyles::FontAwesomeStyles()
    : mstyles{FontAwesomeSolidStyle::create(),
              FontAwesomeRegularStyle::create(),
              FontAwesomeBrandsStyle::create()}
{
}

const FontAwesomeStyles::StylesList& FontAwesomeStyles::all() const
{
  return mstyles;
}

IFontAwesomeStylePtr FontAwesomeStyles::byName(
    const std::string& styleName) const
{
  const auto found =
      std::find_if(mstyles.cbegin(), mstyles.cend(),
                   [&styleName](const IFontAwesomeStylePtr& one) {
                     return one->name() == styleName;
                   });

  if (found != mstyles.cend()) {
    return *found;
  }

  LOGD("No " << styleName << " style in the Font Awesome Free distribution");

  return {};
}

IFontAwesomeStylesPtr FontAwesomeStyles::create()
{
  return std::make_shared<FontAwesomeStyles>();
}

}  // namespace fontawesome
