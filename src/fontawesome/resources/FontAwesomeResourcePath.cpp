#include "src/fontawesome/resources/FontAwesomeResourcePath.h"

#include <cassert>
#include <string>
#include <utility>

#include "src/fontawesome/FontAwesomeIcon.h"
#include "src/log/log.h"

namespace fontawesome
{

FontAwesomeResourcePath::FontAwesomeResourcePath(std::string gprefix)
    : mprefix{normalized(std::move(gprefix))}
{
}

std::string FontAwesomeResourcePath::normalized(std::string gprefix)
{
  while (!gprefix.empty() && gprefix.back() == '/') {
    gprefix.pop_back();
  }

  if (gprefix.empty() || gprefix.front() != '/') {
    gprefix.insert(gprefix.cbegin(), '/');
  }

  return gprefix;
}

const std::string& FontAwesomeResourcePath::prefix() const { return mprefix; }

std::string FontAwesomeResourcePath::prefixedAlias(
    const FontAwesomeIconPtr& icon) const
{
  assert(icon != nullptr);

  if (icon == nullptr) {
    LOGE("No icon to give the resource path of");
    return {};
  }

  return mprefix + "/" + icon->alias();
}

}  // namespace fontawesome
