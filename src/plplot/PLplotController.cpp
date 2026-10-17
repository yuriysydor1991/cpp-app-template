#include "src/plplot/PLplotController.h"

#include <plplot/plplot.h>
#include <plplot/plstream.h>

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "src/log/log.h"
#include "src/plplot/PLplotDevicePicker.h"

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

  const std::string device = PLplotDevicePicker{}.pick(installed_devices());

  if (device.empty()) {
    LOGE(
        "No interactive PLplot device is installed, install the "
        "plplot-driver-qt, the plplot-driver-cairo or the plplot-driver-xwin "
        "package");
    return false;
  }

  // The logarithmic axis of the PLplot takes the log10 values of the data.
  std::vector<PLFLT> logY(n);

  std::transform(y.begin(), y.end(), logY.begin(),
                 [](const PLFLT value) { return std::log10(value); });

  LOGI("Showing the default example exponential logarithmic plot on the "
       << device << " device");

  // Create PLplot C++ stream
  plstream pls;

  pls.sdev(device.c_str());

  // Initialize
  pls.init();

  // Set plotting environment:
  // xmin, xmax, ymin, ymax, just, axis
  // axis = 20 -> logarithmic Y axis of the log10 data
  pls.env(0.0, x.back(), logY.front(), logY.back(), 0, 20);

  // Labels
  pls.lab("X", "exp(X)", "Exponential Growth (log scale)");

  // Draw line
  pls.line(n, x.data(), logY.data());

  return true;
}

std::vector<std::string> PLplotController::installed_devices()
{
  // The PLplot fills the caller's arrays with the device keywords of the
  // drivers it has found and leaves a null pointer after the last one.
  static constexpr const int maxDevices = 128;

  std::vector<const char*> menus(maxDevices, nullptr);
  std::vector<const char*> names(maxDevices, nullptr);

  const char** menusData = menus.data();
  const char** namesData = names.data();
  int count = maxDevices;

  plgDevs(&menusData, &namesData, &count);

  std::vector<std::string> devices;

  const auto found = static_cast<std::size_t>(std::max(count, 0));

  for (std::size_t index = 0; index < found && names[index] != nullptr;
       ++index) {
    devices.emplace_back(names[index]);
  }

  return devices;
}

}  // namespace plploti
