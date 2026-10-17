#include "src/freesoundaudio/categories/FreesoundCategories.h"

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <string>

#include "src/freesoundaudio/categories/FreesoundCategory.h"
#include "src/freesoundaudio/categories/IFreesoundCategories.h"
#include "src/freesoundaudio/categories/IFreesoundCategory.h"
#include "src/freesoundaudio/sounds/FreesoundGeneratedSounds.h"

namespace freesoundaudio
{

FreesoundCategories::FreesoundCategories()
{
  const auto& categoryNames = FreesoundGeneratedSounds::categories();

  mcategories.reserve(categoryNames.size());

  std::transform(categoryNames.cbegin(), categoryNames.cend(),
                 std::back_inserter(mcategories), [](const auto& categoryName) {
                   return FreesoundCategory::create(categoryName);
                 });
}

const FreesoundCategories::CategoriesList& FreesoundCategories::all() const
{
  return mcategories;
}

IFreesoundCategoryPtr FreesoundCategories::find(
    const std::string& categoryName) const
{
  const auto found = std::find_if(mcategories.cbegin(), mcategories.cend(),
                                  [&categoryName](const auto& category) {
                                    return category->name() == categoryName;
                                  });

  return found == mcategories.cend() ? IFreesoundCategoryPtr{} : *found;
}

std::size_t FreesoundCategories::count() const { return mcategories.size(); }

IFreesoundCategoriesPtr FreesoundCategories::create()
{
  return std::make_shared<FreesoundCategories>();
}

}  // namespace freesoundaudio
