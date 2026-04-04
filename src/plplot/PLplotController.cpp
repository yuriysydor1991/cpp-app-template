#include "src/plplot/PLplotController.h"

#include <plplot/plstream.h>

#include <algorithm>
#include <cassert>
#include <cmath>
#include <memory>

#include "src/log/log.h"

namespace plploti
{

bool PLplotController::run(std::shared_ptr<app::ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return false;
  }

  LOGI("Your plots are going here.");

  return draw_simple_plot();
}

PLplotControllerPtr PLplotController::create()
{
  return std::make_shared<PLplotController>();
}

bool PLplotController::draw_simple_plot()
{
  static constexpr const unsigned int n = 100;

  std::vector<PLFLT> x(n), y(n);

  std::generate(x.begin(), x.end(), [i = 0]() mutable { return i++ * 0.1; });
  std::generate(y.begin(), y.end(),
                [xter = x.begin()]() mutable { return std::exp(*(xter++)); });

  LOGI("Showing the default example exponential logarithmic plot");

  // Create PLplot C++ stream
  plstream pls;

  // Use Qt widget device (others are also supported)
  pls.sdev("qtwidget");

  // Initialize
  pls.init();

  // Set plotting environment:
  // xmin, xmax, ymin, ymax, just, axis
  // axis = 1 -> logarithmic Y axis
  pls.env(0.0, x.back(), y.front(), y.back(), 0, 1);

  // Labels
  pls.lab("X", "exp(X)", "Exponential Growth (log scale)");

  // Draw line
  pls.line(n, x.data(), y.data());

  return true;
}

}  // namespace plploti
