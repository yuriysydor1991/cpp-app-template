#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTGENERATEDSOUNDS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTGENERATEDSOUNDS_CLASS_H

#include <string>
#include <vector>

namespace opengameartaudio
{

/**
 * @brief The sound file paths of the OpenGameArt packs the project has been
 * configured with.
 *
 * The implementation file is generated into the build directory by the
 * cmake/enablers/audio/template-project-opengameart-audio-index-generator.cmake
 * module out of the very packs in use, so the complete sound set ends up
 * compiled into the binary and no directory ever gets scanned at the run time.
 */
class OpenGameArtGeneratedSounds
{
 public:
  using NamesList = std::vector<std::string>;

  /**
   * @brief Gives the names of every pack the configured directory carries.
   *
   * @return Returns the sorted pack names.
   */
  static const NamesList& packs();

  /**
   * @brief Gives the pack relative paths of every sound the given pack ships.
   *
   * @param packName The pack name of interest, the "interface-sounds" one for
   * example.
   *
   * @return Returns the sorted sound paths, an empty list when the directory
   * carries no such pack.
   */
  static const NamesList& names(const std::string& packName);

  /**
   * @brief Gives the license the given pack was published under.
   *
   * @param packName The pack name of interest.
   *
   * @return Returns the license, an empty string when the manifest recorded
   * none for such a pack.
   */
  static const std::string& license(const std::string& packName);
};

}  // namespace opengameartaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTGENERATEDSOUNDS_CLASS_H
