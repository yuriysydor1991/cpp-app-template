#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDSOUND_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDSOUND_CLASS_H

#include <memory>
#include <string>

#include "src/freesoundaudio/categories/IFreesoundCategory.h"

namespace freesoundaudio
{

/**
 * @brief A single sound file of a Freesound CC0 category.
 *
 * Pairs a category with the path of a sound file inside it and derives every
 * name the surrounding code asks the pair for: the plain sound name, the file
 * name, the resource alias and the absolute path of the very sound file.
 */
class FreesoundSound
{
 public:
  using FreesoundSoundPtr = std::shared_ptr<FreesoundSound>;

  virtual ~FreesoundSound() = default;

  /**
   * @brief Constructs the sound of the given category and category relative
   * path.
   *
   * A category ships it's files under a subdirectory of it's own, which differs
   * from category to category, so the path stays whole instead of a plain file
   * name.
   *
   * @param gcategory The category the sound belongs to.
   * @param gpath The sound file path relative to the category directory, the
   * "Audio/click_001.ogg" one for example.
   */
  FreesoundSound(IFreesoundCategoryPtr gcategory, std::string gpath);

  /**
   * @brief Gives the category the sound belongs to.
   */
  const IFreesoundCategoryPtr& category() const;

  /**
   * @brief Gives the sound file path relative to the category directory.
   *
   * @return Returns the relative path, the "Audio/click_001.ogg" one for
   * example.
   */
  const std::string& path() const;

  /**
   * @brief Gives the sound file name.
   *
   * @return Returns the file name, the "click_001.ogg" one for example.
   */
  std::string fileName() const;

  /**
   * @brief Gives the plain sound name with no path or extension parts.
   *
   * @return Returns the name, the "click_001" one for example.
   */
  std::string name() const;

  /**
   * @brief Gives the sound file extension with no leading dot.
   *
   * @return Returns the extension, the "ogg" one for example, an empty string
   * for a file carrying none.
   */
  std::string extension() const;

  /**
   * @brief Gives the alias every generated resource manifest keys the sound by.
   *
   * Both the .qrc and the .gresource.xml manifests the freesound audio
   * enabler writes carry this very alias, so it is the single name the compiled
   * in resource and the code below agree upon. It is, at the same time, the
   * path of the sound file relative to the categories root directory.
   *
   * @return Returns the alias, the "interface-sounds/Audio/click_001.ogg" one
   * for example.
   */
  std::string alias() const;

  /**
   * @brief Gives the absolute path of the sound file inside the categories
   * directory the project has been configured with.
   *
   * @return Returns the absolute path of the sound file.
   */
  std::string filePath() const;

  /**
   * @brief Gives the license the very sound file was published under.
   *
   * Freesound publishes it's sounds under several different licenses, one per
   * sound rather than one per collection, so the license recorded in the
   * sounds manifest travels with the single sound itself.
   *
   * @return Returns the license, the "CC0-1.0" one for example, an empty
   * string when the manifest recorded none.
   */
  std::string license() const;

  /**
   * @brief Gives the page the sound file was taken from.
   *
   * Keeping the source next to the license is what makes the attribution of a
   * CC-BY sound - and the provenance of every other one - possible at all.
   *
   * @return Returns the source URL, an empty string when the manifest recorded
   * none.
   */
  std::string sourceUrl() const;

  static FreesoundSoundPtr create(IFreesoundCategoryPtr gcategory,
                                  std::string gpath);

 private:
  IFreesoundCategoryPtr mcategory;
  std::string mpath;
};

using FreesoundSoundPtr = FreesoundSound::FreesoundSoundPtr;

}  // namespace freesoundaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDSOUND_CLASS_H
