#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDPACKS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDPACKS_CLASS_H

#include <cstddef>
#include <string>

#include "src/freesoundaudio/categories/IFreesoundCategories.h"
#include "src/freesoundaudio/categories/IFreesoundCategory.h"

namespace freesoundaudio
{

/**
 * @brief The categories of the generated index.
 *
 * Builds it's set out of the FreesoundGeneratedSounds index alone, so it
 * carries exactly the categories the project has been configured with and
 * reaches no directory at the run time.
 */
class FreesoundCategories : public IFreesoundCategories
{
 public:
  FreesoundCategories();

  const CategoriesList& all() const override;

  IFreesoundCategoryPtr find(const std::string& categoryName) const override;

  std::size_t count() const override;

  static IFreesoundCategoriesPtr create();

 private:
  CategoriesList mcategories;
};

}  // namespace freesoundaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDPACKS_CLASS_H
