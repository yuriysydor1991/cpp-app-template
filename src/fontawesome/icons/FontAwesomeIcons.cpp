#include "src/fontawesome/icons/FontAwesomeIcons.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <memory>
#include <string>
#include <utility>

#include "src/fontawesome/FontAwesomeIcon.h"
#include "src/fontawesome/icons/FontAwesomeGeneratedIcons.h"
#include "src/fontawesome/icons/IFontAwesomeIcons.h"
#include "src/fontawesome/styles/FontAwesomeStyles.h"
#include "src/fontawesome/styles/IFontAwesomeStyles.h"
#include "src/log/log.h"

namespace fontawesome
{

FontAwesomeIcons::FontAwesomeIcons(IFontAwesomeStylesPtr gstyles)
    : mstyles{std::move(gstyles)}
{
  assert(mstyles != nullptr);

  gather();
}

void FontAwesomeIcons::gather()
{
  if (mstyles == nullptr) {
    LOGE("No styles registry to gather the Font Awesome icons of");
    return;
  }

  for (const auto& style : mstyles->all()) {
    assert(style != nullptr);

    const std::string styleName = style->name();
    const auto& names = FontAwesomeGeneratedIcons::names(styleName);

    if (names.empty()) {
      LOGW("The Font Awesome checkout carries no " << styleName
                                                   << " style icons");
      continue;
    }

    micons.reserve(micons.size() + names.size());

    std::transform(names.cbegin(), names.cend(), std::back_inserter(micons),
                   [&style](const std::string& name) {
                     return FontAwesomeIcon::create(style, name);
                   });

    LOGD("Gathered " << names.size() << " " << styleName
                     << " style Font Awesome icons");
  }

  LOGI("Font Awesome icons available: " << micons.size());
}

const FontAwesomeIcons::IconsList& FontAwesomeIcons::all() const
{
  return micons;
}

FontAwesomeIcons::IconsList FontAwesomeIcons::ofStyle(
    const std::string& styleName) const
{
  IconsList found;

  std::copy_if(micons.cbegin(), micons.cend(), std::back_inserter(found),
               [&styleName](const FontAwesomeIconPtr& icon) {
                 return icon->style()->name() == styleName;
               });

  return found;
}

FontAwesomeIconPtr FontAwesomeIcons::find(const std::string& styleName,
                                          const std::string& iconName) const
{
  const auto found = std::find_if(
      micons.cbegin(), micons.cend(),
      [&styleName, &iconName](const FontAwesomeIconPtr& icon) {
        return icon->name() == iconName && icon->style()->name() == styleName;
      });

  if (found != micons.cend()) {
    return *found;
  }

  LOGD("No " << styleName << "/" << iconName << " Font Awesome icon");

  return {};
}

FontAwesomeIcons::IconsList FontAwesomeIcons::search(
    const std::string& namePart) const
{
  IconsList found;

  if (namePart.empty()) {
    return found;
  }

  std::copy_if(micons.cbegin(), micons.cend(), std::back_inserter(found),
               [&namePart](const FontAwesomeIconPtr& icon) {
                 return icon->name().find(namePart) != std::string::npos;
               });

  return found;
}

std::size_t FontAwesomeIcons::count() const { return micons.size(); }

IFontAwesomeIconsPtr FontAwesomeIcons::create()
{
  return std::make_shared<FontAwesomeIcons>(FontAwesomeStyles::create());
}

}  // namespace fontawesome
