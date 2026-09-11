#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IFREESOUNDPACKS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IFREESOUNDPACKS_CLASS_H

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "src/freesoundaudio/categories/IFreesoundCategory.h"

namespace freesoundaudio
{

/**
 * @brief Every Freesound sound category the project has been configured with.
 */
class IFreesoundCategories
{
 public:
  using IFreesoundCategoriesPtr = std::shared_ptr<IFreesoundCategories>;
  using CategoriesList = std::vector<IFreesoundCategoryPtr>;

  virtual ~IFreesoundCategories() = default;

  /**
   * @brief Gives every available category, ordered by the category name.
   */
  virtual const CategoriesList& all() const = 0;

  /**
   * @brief Searches for the category of the given name.
   *
   * @param categoryName The category name of interest.
   *
   * @return Returns the category or a nullptr one when none carries such a
   * name.
   */
  virtual IFreesoundCategoryPtr find(const std::string& categoryName) const = 0;

  /**
   * @brief Gives the count of the available categories.
   */
  virtual std::size_t count() const = 0;
};

using IFreesoundCategoriesPtr = IFreesoundCategories::IFreesoundCategoriesPtr;

}  // namespace freesoundaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IFREESOUNDPACKS_CLASS_H
