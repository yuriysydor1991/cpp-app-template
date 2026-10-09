#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GETTEXTCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GETTEXTCONTROLLER_CLASS_H

#include <memory>
#include <string>

namespace gettexti
{

/**
 * @brief The GNU gettext translations controller. It activates the messages
 * locale of the user environment and binds a text domain to the directory of
 * it's compiled catalogs, so the gettexti::tr and the gettexti::trn calls of
 * the src/gettext/tr.h header translate into the language of the user.
 *
 * The libintl keeps the locale and the bindings process wide. Nothing throws:
 * the failures are logged and reported through the return values.
 */
class GettextController
{
 public:
  using GettextControllerPtr = std::shared_ptr<GettextController>;

  virtual ~GettextController() = default;
  GettextController() = default;

  /**
   * @brief Binds the project text domain (the project binary name) to the
   * catalogs directory the CatalogsLocator class finds for the running
   * executable.
   *
   * @param execPath The executable path, usually the first command line
   * argument. May be empty.
   *
   * @return Returns true on success and false otherwise.
   */
  virtual bool init(const std::string& execPath);

  /**
   * @brief Activates the messages locale of the user environment (the LC_ALL,
   * the LC_MESSAGES or the LANG variable, while the LANGUAGE one may list the
   * languages to try) and makes the domain the default one with it's catalogs
   * in the directory and the translations given in the UTF-8.
   *
   * @param domain The text domain, the name of the domain.mo catalog files.
   * @param localeDir The directory of the language/LC_MESSAGES/domain.mo
   * catalogs.
   *
   * @return Returns true on success and false otherwise.
   */
  virtual bool bind(const std::string& domain, const std::string& localeDir);

  /**
   * @brief Creates a controller instance.
   *
   * @return The created controller.
   */
  static GettextControllerPtr create();
};

using GettextControllerPtr = GettextController::GettextControllerPtr;

}  // namespace gettexti

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GETTEXTCONTROLLER_CLASS_H
