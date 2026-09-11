#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDSOUNDS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDSOUNDS_CLASS_H

#include <cstddef>
#include <string>

#include "src/freesoundaudio/FreesoundSound.h"
#include "src/freesoundaudio/categories/IFreesoundCategories.h"
#include "src/freesoundaudio/sounds/IFreesoundSounds.h"

namespace freesoundaudio
{

/**
 * @brief The sound set of the generated index.
 *
 * Builds it's set out of the FreesoundGeneratedSounds index alone, so it
 * carries exactly the sounds the project has been configured with and reaches
 * no directory at the run time.
 */
class FreesoundSounds : public IFreesoundSounds
{
 public:
  /**
   * @brief Constructs the set out of the given categories.
   *
   * @param gpacks The categories to gather the sounds of.
   */
  explicit FreesoundSounds(IFreesoundCategoriesPtr gpacks);

  const SoundsList& all() const override;

  SoundsList ofCategory(const std::string& categoryName) const override;

  FreesoundSoundPtr find(const std::string& categoryName,
                         const std::string& soundPath) const override;

  SoundsList search(const std::string& namePart) const override;

  std::size_t count() const override;

  static IFreesoundSoundsPtr create();

  static IFreesoundSoundsPtr create(IFreesoundCategoriesPtr gpacks);

 private:
  SoundsList msounds;
};

}  // namespace freesoundaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDSOUNDS_CLASS_H
