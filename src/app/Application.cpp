#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/log/log.h"
#include "src/wt4/Wt4Server.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  if (wt4server::Wt4Server::run(ctx) != 0) {
    LOGE("Wt4 controller returned invalid status");
    return INVALID;
  }

  return 0;
}

}  // namespace app
