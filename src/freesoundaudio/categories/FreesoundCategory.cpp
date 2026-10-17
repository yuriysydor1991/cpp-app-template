#include "src/freesoundaudio/categories/FreesoundCategory.h"

#include <memory>
#include <string>
#include <utility>

#include "src/freesoundaudio/categories/IFreesoundCategory.h"

namespace freesoundaudio
{

FreesoundCategory::FreesoundCategory(std::string gname)
    : mname{std::move(gname)}
{
}

std::string FreesoundCategory::name() const { return mname; }

IFreesoundCategoryPtr FreesoundCategory::create(std::string gname)
{
  return std::make_shared<FreesoundCategory>(std::move(gname));
}

}  // namespace freesoundaudio
