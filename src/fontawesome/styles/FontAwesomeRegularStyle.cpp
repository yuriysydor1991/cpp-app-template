#include "src/fontawesome/styles/FontAwesomeRegularStyle.h"

#include <memory>
#include <string>

#include "src/fontawesome/styles/IFontAwesomeStyle.h"

namespace fontawesome
{

std::string FontAwesomeRegularStyle::name() const { return "regular"; }

std::string FontAwesomeRegularStyle::webfontFileName() const
{
  return "fa-regular-400.woff2";
}

IFontAwesomeStylePtr FontAwesomeRegularStyle::create()
{
  return std::make_shared<FontAwesomeRegularStyle>();
}

}  // namespace fontawesome
