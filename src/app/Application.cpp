#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/log/log.h"
#include "src/plplot/PLplotController.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  plploti::PLplotControllerPtr plotter = plploti::PLplotController::create();

  assert(plotter != nullptr);

  if (plotter == nullptr) {
    LOGE("No plotter instance found");
    return INVALID;
  }

  if (!plotter->run(ctx)) {
    LOGE("Plotter instance returned invalid status");
    return INVALID;
  }

  return 0;
}

}  // namespace app
