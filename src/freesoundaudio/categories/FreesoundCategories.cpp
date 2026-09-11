#include "src/freesoundaudio/categories/FreesoundCategories.h"

#include <cstddef>
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

  for (const auto& categoryName : categoryNames) {
    mcategories.push_back(FreesoundCategory::create(categoryName));
  }
}

const FreesoundCategories::CategoriesList& FreesoundCategories::all() const
{
  return mcategories;
}

IFreesoundCategoryPtr FreesoundCategories::find(
    const std::string& categoryName) const
{
  for (const auto& category : mcategories) {
    if (category->name() == categoryName) {
      return category;
    }
  }

  return {};
}

std::size_t FreesoundCategories::count() const { return mcategories.size(); }

IFreesoundCategoriesPtr FreesoundCategories::create()
{
  return std::make_shared<FreesoundCategories>();
}

}  // namespace freesoundaudio
