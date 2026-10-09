#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CATALOGSLOCATOR_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CATALOGSLOCATOR_CLASS_H

#include <string>

/**
 * @brief The namespace of the GNU gettext translations integration classes.
 */
namespace gettexti
{

/**
 * @brief Finds the directory of the compiled message catalogs for the
 * executable: the one next to it, which the relocatable packages (e.g. the
 * AppImage and the snap ones) keep wherever they are mounted to, the build
 * tree one and the installation one, in that order.
 */
class CatalogsLocator
{
 public:
  /**
   * @param relative The catalogs directory relative to the executable one.
   * @param build The catalogs directory of the build tree.
   * @param install The catalogs installation directory.
   */
  CatalogsLocator(std::string relative, std::string build, std::string install);

  /**
   * @brief Gives the first existing catalogs directory of the executable.
   *
   * @param execPath The executable path, usually the first command line
   * argument. A bare executable name, looked up through the PATH, tells
   * nothing about the directory of the executable and is skipped like an
   * empty one.
   *
   * @return Returns the directory found or the installation one if none of
   * them exists.
   */
  std::string locate(const std::string& execPath) const;

  /**
   * @brief Gives the path of the running executable: the target of the
   * /proc/self/exe link on Linux, which names the executable started through
   * the PATH too (e.g. the /usr/bin one of a DEB package, whose prefix differs
   * from the configured one), or the given path otherwise.
   *
   * @param execPath The executable path, usually the first command line
   * argument.
   *
   * @return Returns the executable path.
   */
  static std::string executable(const std::string& execPath);

 private:
  std::string relativeDir;
  std::string buildDir;
  std::string installDir;
};

}  // namespace gettexti

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CATALOGSLOCATOR_CLASS_H
