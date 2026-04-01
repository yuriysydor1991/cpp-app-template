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

  matplotxxi::MatPlotxxControllerPtr ploter =
      matplotxxi::MatPlotxxController::create();

  assert(ploter != nullptr);

  if (!ploter->run(ctx)) {
    LOGE("Plotter signalled about fail status");
    return INVALID;
  }

  return 0;
}

}  // namespace app
