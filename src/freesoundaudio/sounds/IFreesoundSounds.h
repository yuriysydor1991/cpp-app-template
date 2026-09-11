#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IFREESOUNDSOUNDS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IFREESOUNDSOUNDS_CLASS_H

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "src/freesoundaudio/FreesoundSound.h"

namespace freesoundaudio
{

/**
 * @brief The whole sound set of the Freesound categories the project has been
 * configured with.
 *
 * Every sound of every configured category is reachable here, so the
 * application code picks the ones it needs (and hands them over to the resource
 * system of it's GUI toolkit) without a single sound name written into the
 * sources by hand.
 */
class IFreesoundSounds
{
 public:
  using IFreesoundSoundsPtr = std::shared_ptr<IFreesoundSounds>;
  using SoundsList = std::vector<FreesoundSoundPtr>;

  virtual ~IFreesoundSounds() = default;

  /**
   * @brief Gives every sound of every category, ordered by the category and
   * then by the sound path.
   *
   * @return Returns the whole sound set.
   */
  virtual const SoundsList& all() const = 0;

  /**
   * @brief Gives every sound of the given category.
   *
   * @param categoryName The category name of interest, the "interface-sounds"
   * one for example.
   *
   * @return Returns the sounds of the category, an empty list when the set
   * carries no such category.
   */
  virtual SoundsList ofCategory(const std::string& categoryName) const = 0;

  /**
   * @brief Searches for the sound of the given category and category relative
   * path.
   *
   * @param categoryName The category name of interest.
   * @param soundPath The sound file path relative to the category directory,
   * the "Audio/click_001.ogg" one for example.
   *
   * @return Returns the sound or a nullptr one when the set carries none.
   */
  virtual FreesoundSoundPtr find(const std::string& categoryName,
                                 const std::string& soundPath) const = 0;

  /**
   * @brief Gives every sound which plain name contains the given part.
   *
   * The counterpart of a "find the sounds of interest by hand" browse over the
   * categories, so no file manager and no audio player is needed to look one
   * up.
   *
   * @param namePart The sound name part to look for, the "click" one for
   * example.
   *
   * @return Returns the matching sounds of every category.
   */
  virtual SoundsList search(const std::string& namePart) const = 0;

  /**
   * @brief Gives the count of the sounds the whole set carries.
   */
  virtual std::size_t count() const = 0;
};

using IFreesoundSoundsPtr = IFreesoundSounds::IFreesoundSoundsPtr;

}  // namespace freesoundaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IFREESOUNDSOUNDS_CLASS_H
