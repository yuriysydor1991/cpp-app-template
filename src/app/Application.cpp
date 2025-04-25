#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/wt4/Wt4Server.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    return INVALID;
  }

  return wt4server::Wt4Server::run(ctx);
}

}  // namespace app
