#include "src/pgplot/PGPLOTController.h"

#include <cpgplot.h>

#include <algorithm>
#include <cassert>
#include <cmath>
#include <memory>
#include <vector>

#include "src/log/log.h"

namespace pgploti
{

namespace
{

/**
 * @brief The PGPLOT device to draw the plots onto.
 *
 * The "/XWINDOW" one is the interactive X11 window device. Replace it with any
 * other device supported by your PGPLOT installation ("/PNG", "/PS", "/SVG",
 * "/NULL" and so on) in order to store the plots into a file instead.
 */
constexpr const char* const plotDevice = "/XWINDOW";

}  // namespace

bool PGPLOTController::run(std::shared_ptr<app::ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return false;
  }

  LOGI("Your plots are going here.");

  return draw_simple_plot();
}

PGPLOTControllerPtr PGPLOTController::create()
{
  return std::make_shared<PGPLOTController>();
}

bool PGPLOTController::draw_simple_plot()
{
  static constexpr const int n = 100;

  std::vector<float> x(n), y(n);

  std::generate(x.begin(), x.end(),
                [i = 0]() mutable { return static_cast<float>(i++) * 0.1F; });

  // unlike the axes themselves, the PGPLOT plotting routines are not aware of
  // the logarithmic scale, so the already logarithmed values are passed
  std::transform(x.begin(), x.end(), y.begin(),
                 [](const float xv) { return std::log10(std::exp(xv)); });

  LOGI("Showing the default example exponential logarithmic plot");

  const int deviceId = cpgopen(plotDevice);

  if (deviceId <= 0) {
    LOGE("Fail to open the " << plotDevice << " PGPLOT device");
    return false;
  }

  // Set plotting environment:
  // xmin, xmax, ymin, ymax, just, axis
  // axis = 20 -> logarithmic Y axis
  cpgenv(x.front(), x.back(), y.front(), y.back(), 0, 20);

  // Labels
  cpglab("X", "exp(X)", "Exponential Growth (log scale)");

  // Draw line
  cpgline(n, x.data(), y.data());

  cpgclos();

  return true;
}

}  // namespace pgploti
