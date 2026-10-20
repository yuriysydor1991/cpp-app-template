#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_DATALOCATOR_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_DATALOCATOR_CLASS_H

#include <string>

namespace app
{

/**
 * @brief Locates the data files (the models, for example) the running binary
 * loads by default.
 *
 * The install step copies the downloaded data files into the data directory
 * of the project, so an installed binary finds them relative to it's own
 * location (which keeps a relocated package, an AppImage for example, working)
 * or under the configured installation prefix, while a binary run out of the
 * build tree finds the configured ones.
 */
class DataLocator
{
 public:
  /**
   * @brief Gives the copy of the given data file (or directory) the running
   * binary loads: the one installed relative to the binary, the given one or
   * the one installed under the configured prefix, whichever exists first,
   * the given one when none does.
   *
   * @param path The configured data file, the downloaded one of the build
   * tree for example.
   */
  static std::string locate(const std::string& path);

  /**
   * @brief Gives the directory of the running executable file, an empty
   * string when the system names none.
   */
  static std::string executable_directory();
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DATALOCATOR_CLASS_H
