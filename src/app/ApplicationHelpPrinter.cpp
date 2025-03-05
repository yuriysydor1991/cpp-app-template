#include <memory>
#include <iostream>
#include <cassert>

#include "src/app/ApplicationHelpPrinter.h"

namespace app {

int ApplicationHelpPrinter::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr)
  { return INVALID ; }

  // Register and implement here command line parameters from the CommandLineParser class.
  std::cout << "Application help message here!" << std::endl;

  return 0 ;
}

} // namespace app
