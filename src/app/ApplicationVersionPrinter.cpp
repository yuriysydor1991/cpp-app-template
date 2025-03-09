#include "src/app/ApplicationVersionPrinter.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "project-global-decls.h"

namespace app
{

int ApplicationVersionPrinter::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    return INVALID;
  }

  std::cout << project_decls::PROJECT_NAME << " version "
            << project_decls::PROJECT_BUILD_VERSION << std::endl
            << "configure date " << project_decls::PROJECT_CONFIGURE_DATE
            << std::endl
            << "git commit " << project_decls::PROJECT_BUILD_COMMIT
            << std::endl;

  return 0;
}

}  // namespace app
