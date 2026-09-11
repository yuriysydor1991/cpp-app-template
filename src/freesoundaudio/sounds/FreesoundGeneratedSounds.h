#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDGENERATEDSOUNDS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDGENERATEDSOUNDS_CLASS_H

#include <string>
#include <vector>

namespace freesoundaudio
{

/**
 * @brief The sound file paths of the Freesound categories the project has been
 * configured with.
 *
 * The implementation file is generated into the build directory by the
 * cmake/enablers/audio/template-project-freesound-audio-index-generator.cmake
 * module out of the very categories in use, so the complete sound set ends up
 * compiled into the binary and no directory ever gets scanned at the run time.
 */
class FreesoundGeneratedSounds
{
 public:
  using NamesList = std::vector<std::string>;

  /**
   * @brief Gives the names of every category the configured directory carries.
   *
   * @return Returns the sorted category names.
   */
  static const NamesList& categories();

  /**
   * @brief Gives the category relative paths of every sound the given category
   * ships.
   *
   * @param categoryName The category name of interest, the "interface-sounds"
   * one for example.
   *
   * @return Returns the sorted sound paths, an empty list when the directory
   * carries no such category.
   */
  static const NamesList& names(const std::string& categoryName);

  /**
   * @brief Gives the license the given sound was published under.
   *
   * @param soundAlias The "<category>/<path>" alias of the sound.
   *
   * @return Returns the license, an empty string when the manifest recorded
   * none for such a sound.
   */
  static const std::string& license(const std::string& soundAlias);

  /**
   * @brief Gives the page the given sound was taken from.
   *
   * @param soundAlias The "<category>/<path>" alias of the sound.
   *
   * @return Returns the source URL, an empty string when the manifest recorded
   * none for such a sound.
   */
  static const std::string& sourceUrl(const std::string& soundAlias);
};

}  // namespace freesoundaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FREESOUNDGENERATEDSOUNDS_CLASS_H
