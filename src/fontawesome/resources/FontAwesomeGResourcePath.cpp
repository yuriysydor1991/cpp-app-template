#include "src/fontawesome/resources/FontAwesomeGResourcePath.h"

#include <memory>
#include <string>
#include <utility>

#include "fontawesome-decls.h"
#include "src/fontawesome/FontAwesomeIcon.h"
#include "src/fontawesome/resources/FontAwesomeResourcePath.h"
#include "src/fontawesome/resources/IFontAwesomeResourcePath.h"

namespace fontawesome
{

FontAwesomeGResourcePath::FontAwesomeGResourcePath(std::string gprefix)
    : FontAwesomeResourcePath{std::move(gprefix)}
{
}

std::string FontAwesomeGResourcePath::of(const FontAwesomeIconPtr& icon) const
{
  return prefixedAlias(icon);
}

std::string FontAwesomeGResourcePath::uriOf(
    const FontAwesomeIconPtr& icon) const
{
  const auto alias = prefixedAlias(icon);

  if (alias.empty()) {
    return {};
  }

  return RESOURCE_SCHEME + alias;
}

IFontAwesomeResourcePathPtr FontAwesomeGResourcePath::create()
{
  return create(fontawesome_decls::FONTAWESOME_GRESOURCE_PREFIX);
}

IFontAwesomeResourcePathPtr FontAwesomeGResourcePath::create(
    std::string gprefix)
{
  return std::make_shared<FontAwesomeGResourcePath>(std::move(gprefix));
}

}  // namespace fontawesome
