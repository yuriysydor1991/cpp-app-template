#include "src/matplotxx/MatPlotxxController.h"

#include <matplot/matplot.h>

#include <cassert>
#include <cmath>
#include <memory>
#include <thread>
#include <utility>
#include <vector>

#include "src/log/log.h"

namespace matplotxxi
{

bool MatPlotxxController::run(std::shared_ptr<app::ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return false;
  }

  LOGI("Your MatPlot++ plots declared over here!");

  // taken from
  // https://github.com/alandefreitas/matplotplusplus/blob/master/examples/line_plot/loglog/loglog_1.cpp
  using namespace matplot;

  const std::vector<double> x = logspace(-1, 2);
  const std::vector<double> y = transform(x, [](auto x) { return pow(2, x); });

  loglog(x, y);

  LOGD("Showing the plot window");

  show();

  return true;
}

MatPlotxxControllerPtr MatPlotxxController::create()
{
  return std::make_shared<MatPlotxxController>();
}

}  // namespace matplotxxi
