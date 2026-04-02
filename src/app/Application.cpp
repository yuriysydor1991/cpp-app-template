#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/log/log.h"
#include "src/matplotxx/MatPlotxxController.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  matplotxxi::MatPlotxxControllerPtr plotter =
      matplotxxi::MatPlotxxController::create();

  assert(plotter != nullptr);

  if (plotter == nullptr) {
    LOGE("No plotter instance available");
    return INVALID;
  }

  if (!plotter->run(ctx)) {
    LOGE("Plotter signalled about fail status");
    return INVALID;
  }

  return 0;
}

}  // namespace app
