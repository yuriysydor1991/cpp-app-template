#include "src/fontawesome/resources/FontAwesomeQtResourcePath.h"

#include <memory>
#include <string>
#include <utility>

#include "fontawesome-decls.h"
#include "src/fontawesome/FontAwesomeIcon.h"
#include "src/fontawesome/resources/FontAwesomeResourcePath.h"
#include "src/fontawesome/resources/IFontAwesomeResourcePath.h"

namespace fontawesome
{

FontAwesomeQtResourcePath::FontAwesomeQtResourcePath(std::string gprefix)
    : FontAwesomeResourcePath{std::move(gprefix)}
{
}

std::string FontAwesomeQtResourcePath::of(const FontAwesomeIconPtr& icon) const
{
  const auto alias = prefixedAlias(icon);

  if (alias.empty()) {
    return {};
  }

  return RESOURCE_MARK + alias;
}

std::string FontAwesomeQtResourcePath::uriOf(
    const FontAwesomeIconPtr& icon) const
{
  const auto alias = prefixedAlias(icon);

  if (alias.empty()) {
    return {};
  }

  return RESOURCE_SCHEME + alias;
}

IFontAwesomeResourcePathPtr FontAwesomeQtResourcePath::create()
{
  return create(fontawesome_decls::FONTAWESOME_QT_RESOURCE_PREFIX);
}

IFontAwesomeResourcePathPtr FontAwesomeQtResourcePath::create(
    std::string gprefix)
{
  return std::make_shared<FontAwesomeQtResourcePath>(std::move(gprefix));
}

}  // namespace fontawesome
