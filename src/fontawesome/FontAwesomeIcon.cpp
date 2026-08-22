#include "src/fontawesome/FontAwesomeIcon.h"

#include <cassert>
#include <memory>
#include <string>
#include <utility>

#include "fontawesome-decls.h"
#include "src/fontawesome/styles/IFontAwesomeStyle.h"

namespace fontawesome
{

FontAwesomeIcon::FontAwesomeIcon(IFontAwesomeStylePtr gstyle, std::string gname)
    : mstyle{std::move(gstyle)}, mname{std::move(gname)}
{
  assert(mstyle != nullptr);
  assert(!mname.empty());
}

const IFontAwesomeStylePtr& FontAwesomeIcon::style() const { return mstyle; }

const std::string& FontAwesomeIcon::name() const { return mname; }

std::string FontAwesomeIcon::fileName() const { return mname + SVG_EXTENSION; }

std::string FontAwesomeIcon::alias() const
{
  assert(mstyle != nullptr);

  if (mstyle == nullptr) {
    return fileName();
  }

  return mstyle->name() + "/" + fileName();
}

std::string FontAwesomeIcon::relativePath() const
{
  return SVGS_DIRECTORY_NAME + "/" + alias();
}

std::string FontAwesomeIcon::filePath() const
{
  return fontawesome_decls::FONTAWESOME_SVGS_DIR + "/" + alias();
}

FontAwesomeIconPtr FontAwesomeIcon::create(IFontAwesomeStylePtr gstyle,
                                           std::string gname)
{
  return std::make_shared<FontAwesomeIcon>(std::move(gstyle), std::move(gname));
}

}  // namespace fontawesome
