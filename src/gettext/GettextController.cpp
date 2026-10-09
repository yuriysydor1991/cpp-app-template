#include "src/gettext/GettextController.h"

#include <libintl.h>

#include <clocale>
#include <memory>
#include <string>

#include "project-global-decls.h"
#include "src/gettext/CatalogsLocator.h"
#include "src/log/log.h"

namespace gettexti
{

bool GettextController::init(const std::string& execPath)
{
  const CatalogsLocator locator{project_decls::PROJECT_RELATIVE_LOCALE_DIR,
                                project_decls::PROJECT_BUILD_LOCALE_DIR,
                                project_decls::PROJECT_LOCALE_DIR};

  return bind(project_decls::PROJECT_NAME,
              locator.locate(CatalogsLocator::executable(execPath)));
}

bool GettextController::bind(const std::string& domain,
                             const std::string& localeDir)
{
  // The messages category alone, since the whole locale of the user switches
  // the number formatting too, e.g. the std::stod and the std::to_string
  // calls read and write the 1,5 instead of the 1.5 under the uk_UA one.
  if (setlocale(LC_MESSAGES, "") == nullptr) {
    LOGW(
        "The messages locale of the environment is not installed, so the "
        "messages stay untranslated");
  }

  if (bindtextdomain(domain.c_str(), localeDir.c_str()) == nullptr ||
      bind_textdomain_codeset(domain.c_str(), "UTF-8") == nullptr ||
      textdomain(domain.c_str()) == nullptr) {
    LOGE("Failed to bind the '" << domain << "' text domain to the "
                                << localeDir << " catalogs directory");
    return false;
  }

  LOGD("The '" << domain << "' text domain is bound to the " << localeDir
               << " catalogs directory");

  return true;
}

GettextControllerPtr GettextController::create()
{
  return std::make_shared<GettextController>();
}

}  // namespace gettexti
