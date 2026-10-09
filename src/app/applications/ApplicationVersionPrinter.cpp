#include "src/app/applications/ApplicationVersionPrinter.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "project-global-decls.h"
#include "src/gettext/tr.h"
#include "src/log/log.h"

namespace app
{

using gettexti::tr;

int ApplicationVersionPrinter::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid application context provided");
    return INVALID;
  }

  std::cout << project_decls::PROJECT_NAME << " " << tr("version") << " "
            << project_decls::PROJECT_BUILD_VERSION << std::endl
            << tr("configure date") << " "
            << project_decls::PROJECT_CONFIGURE_DATE << std::endl
            << tr("git commit") << " " << project_decls::PROJECT_BUILD_COMMIT
            << std::endl;

  return 0;
}

}  // namespace app
