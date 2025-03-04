#include <memory>
#include <iostream>
#include <cassert>

#include "src/app/ApplicationVersionPrinter.h"
#include "project-global-decls.h"

namespace app {

int ApplicationVersionPrinter::run([[maybe_unused]] std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  std::cout 
    << project_decls::PROJECT_NAME
    << " version " << project_decls::PROJECT_BUILD_VERSION
    << std::endl
    << "configure date " << project_decls::PROJECT_CONFIGURE_DATE
    << std::endl
    << "git commit " << project_decls::PROJECT_BUILD_COMMIT
    << std::endl;

  return 0 ; 
}

} // namespace app
