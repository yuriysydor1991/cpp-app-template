#include <memory>
#include <iostream>

#include "src/app/Application.h"

namespace app {

int Application::run([[maybe_unused]] std::shared_ptr<ApplicationContext> ctx)
{
  std::cout << "Your application implementation goes here!" << std::endl;

  return 0 ; 
}

} // namespace app
