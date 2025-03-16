#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    return INVALID;
  }

  std::cout << "Your application implementation goes here!" << std::endl;

  return 0;
}

}  // namespace app
