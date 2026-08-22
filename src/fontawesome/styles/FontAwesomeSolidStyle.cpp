#include "src/fontawesome/styles/FontAwesomeSolidStyle.h"

#include <memory>
#include <string>

#include "src/fontawesome/styles/IFontAwesomeStyle.h"

namespace fontawesome
{

std::string FontAwesomeSolidStyle::name() const { return "solid"; }

std::string FontAwesomeSolidStyle::webfontFileName() const
{
  return "fa-solid-900.woff2";
}

IFontAwesomeStylePtr FontAwesomeSolidStyle::create()
{
  return std::make_shared<FontAwesomeSolidStyle>();
}

}  // namespace fontawesome
