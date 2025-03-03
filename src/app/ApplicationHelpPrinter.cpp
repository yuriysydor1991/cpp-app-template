#include <memory>
#include <iostream>

#include "src/app/ApplicationHelpPrinter.h"

namespace app {

int ApplicationHelpPrinter::run([[maybe_unused]] std::shared_ptr<ApplicationContext> ctx)
{
  std::cout << "Application help message here!" << std::endl;

  return 0 ; 
}

} // namespace app