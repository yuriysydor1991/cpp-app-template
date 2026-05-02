#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/log/log.h"
#include "src/plotgencpp/PlotGenCppController.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  plotgencppi::PlotGenCppControllerPtr plotter = plotgencppi::PlotGenCppController::create();

  assert(plotter != nullptr);

  if (plotter == nullptr) {
    LOGE("No valid plotter instance created");
    return INVALID;
  }

  LOGI("Drawing the plot");

  if (!plotter->run(ctx)) {
    LOGE("Plotter returned invalid state");
    return INVALID;
  }

  return 0;
}

}  // namespace app
