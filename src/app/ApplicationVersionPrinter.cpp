#include <memory>
#include <iostream>
#include <cassert>

#include "src/app/ApplicationVersionPrinter.h"

namespace app {

int ApplicationVersionPrinter::run([[maybe_unused]] std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  std::cout << "Your application version goes here!" << std::endl;

  return 0 ; 
}

} // namespace app
