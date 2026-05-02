#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PLOTGETCPPCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PLOTGETCPPCONTROLLER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace plotgencppi
{

/**
 * @brief Interface wrapper class for the PlotGenCpp library functionality.
 */
class PlotGenCppController
{
 public:
  using PlotGenCppControllerPtr = std::shared_ptr<PlotGenCppController>;

  virtual ~PlotGenCppController() = default;
  PlotGenCppController() = default;

  virtual bool run(std::shared_ptr<app::ApplicationContext> ctx);

  static PlotGenCppControllerPtr create();

private:
    bool drawTheExamplePlot();
};

using PlotGenCppControllerPtr = PlotGenCppController::PlotGenCppControllerPtr;

}  // namespace plotgencppi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PLOTGETCPPCONTROLLER_CLASS_H