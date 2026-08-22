#include "src/fontawesome/styles/FontAwesomeBrandsStyle.h"

#include <memory>
#include <string>

#include "src/fontawesome/styles/IFontAwesomeStyle.h"

namespace fontawesome
{

std::string FontAwesomeBrandsStyle::name() const { return "brands"; }

std::string FontAwesomeBrandsStyle::webfontFileName() const
{
  return "fa-brands-400.woff2";
}

IFontAwesomeStylePtr FontAwesomeBrandsStyle::create()
{
  return std::make_shared<FontAwesomeBrandsStyle>();
}

}  // namespace fontawesome
