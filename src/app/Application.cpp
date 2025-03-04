#include <memory>
#include <iostream>
#include <cassert>

#include "src/app/Application.h"

namespace app {

int Application::run([[maybe_unused]] std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr)
  { return INVALID ; }
  
  std::cout << "Your application implementation goes here!" << std::endl;

  return 0 ;
}

} // namespace app
