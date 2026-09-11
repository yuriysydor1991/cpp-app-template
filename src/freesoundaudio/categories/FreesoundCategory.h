#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDPACK_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDPACK_CLASS_H

#include <string>

#include "src/freesoundaudio/categories/IFreesoundCategory.h"

namespace freesoundaudio
{

/**
 * @brief A Freesound sound category named at the run time.
 *
 * The categories to make available are a build option rather than a fixed set,
 * so one descendant carrying the configured name serves every category instead
 * of a hand written class per category.
 */
class FreesoundCategory : public IFreesoundCategory
{
 public:
  /**
   * @brief Constructs the category of the given name.
   *
   * @param gname The category name, the "interface" one for example.
   */
  explicit FreesoundCategory(std::string gname);

  std::string name() const override;

  static IFreesoundCategoryPtr create(std::string gname);

 private:
  std::string mname;
};

}  // namespace freesoundaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDPACK_CLASS_H
