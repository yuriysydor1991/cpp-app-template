#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTROOTDIRECTORY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTROOTDIRECTORY_CLASS_H

#include <string>
#include <vector>

namespace opengameartaudio
{

/**
 * @brief Locates the packs root directory the running binary reads the sounds
 * out of.
 *
 * The install step copies the packs into the data directory next to the
 * binary, so an installed binary finds them relative to it's own location
 * (which keeps a relocated package, an AppImage for example, working) or under
 * the configured installation prefix, while a binary run out of the build tree
 * finds the packs directory the project has been configured with.
 */
class OpenGameArtRootDirectory
{
 public:
  /**
   * @brief Gives the packs root directory, resolved once per process.
   */
  static const std::string& path();

  /**
   * @brief Gives the first existing directory of the given candidates.
   *
   * @param candidates The directories to check, in the order of preference,
   * the empty ones being skipped.
   * @param fallback The directory to give back when no candidate exists.
   */
  static std::string firstExisting(const std::vector<std::string>& candidates,
                                   const std::string& fallback);

  /**
   * @brief Gives the directory of the running executable file, an empty
   * string when the system names none.
   */
  static std::string executableDirectory();
};

}  // namespace opengameartaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGAMEARTROOTDIRECTORY_CLASS_H
