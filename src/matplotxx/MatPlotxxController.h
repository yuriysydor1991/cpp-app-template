#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MATPLOTXXCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MATPLOTXXCONTROLLER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace matplotxxi
{

/**
 * @brief Interface wrapper class for the MatPlot++ library functionality.
 */
class MatPlotxxController
{
 public:
  using MatPlotxxControllerPtr = std::shared_ptr<MatPlotxxController>;

  virtual ~MatPlotxxController() = default;
  MatPlotxxController() = default;

  virtual bool run(std::shared_ptr<app::ApplicationContext> ctx);

  static MatPlotxxControllerPtr create();
};

using MatPlotxxControllerPtr = MatPlotxxController::MatPlotxxControllerPtr;

}  // namespace matplotxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MATPLOTXXCONTROLLER_CLASS_H
