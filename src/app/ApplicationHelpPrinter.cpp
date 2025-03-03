#include <memory>
#include <iostream>
#include <cassert>

#include "src/app/ApplicationHelpPrinter.h"

namespace app {

int ApplicationHelpPrinter::run([[maybe_unused]] std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr)
  { return INVALID ; }

  std::cout << "Application help message here!" << std::endl;

  return 0 ;
}

} // namespace app