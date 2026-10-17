#include "src/matplotxx/MatPlotxxController.h"

#include <matplot/matplot.h>

#include <cassert>
#include <cerrno>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <system_error>
#include <utility>
#include <vector>

#if !defined(_WIN32)
#include <poll.h>
#include <unistd.h>
#endif

#include "src/log/log.h"

namespace matplotxxi
{

namespace
{

/**
 * @brief Builds the example plot into a figure drawn by a gnuplot process of
 * its own, which lives as long as the figure does.
 */
matplot::figure_handle make_example_figure()
{
  // taken from
  // https://github.com/alandefreitas/matplotplusplus/blob/master/examples/line_plot/loglog/loglog_1.cpp
  const std::vector<double> x = matplot::logspace(-1, 2);
  const std::vector<double> y =
      matplot::transform(x, [](const double xv) { return std::pow(2, xv); });

  auto figure = std::make_shared<matplot::figure_type>(true);

  // The quiet figure gets its backend on the first draw call alone, which
  // the save call relies on being there already.
  figure->backend(matplot::create_default_backend());
  figure->current_axes()->loglog(x, y);

  return figure;
}

}  // namespace

bool MatPlotxxController::run(std::shared_ptr<app::ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return false;
  }

  LOGI("Your MatPlot++ plots declared over here!");

  const auto figure = make_example_figure();

  figure->draw();

  LOGI("Showing the plot window, press ENTER to close it");

  wait_for_enter_or_stop(ctx);

  return true;
}

void MatPlotxxController::wait_for_enter_or_stop(
    const std::shared_ptr<app::ApplicationContext>& ctx)
{
#if defined(_WIN32)
  // No poll call there, so the stop flag is checked after the ENTER key alone.
  std::cin.get();
#else
  // The standard input is polled instead of read, so the raised stop flag ends
  // the wait with no ENTER key pressed and no reader left blocked in it.
  pollfd input{STDIN_FILENO, POLLIN, 0};

  while (!ctx->get_stop()) {
    const int ready =
        poll(&input, 1, static_cast<int>(STOP_CHECK_PERIOD.count()));

    if (ready > 0) {
      // The ENTER key, the end of the input or no input at all.
      std::cin.get();
      return;
    }

    if (ready < 0 && errno != EINTR) {
      return;
    }
  }
#endif
}

bool MatPlotxxController::save(const std::string& path)
{
  // The gnuplot process of the temporary figure completes the file once it
  // exits together with the figure, so the file is checked only afterwards
  // and a stale one is dropped beforehand.
  std::error_code ignored;
  std::filesystem::remove(path, ignored);

  const bool drawn = make_example_figure()->save(path);

  if (!drawn || !std::filesystem::exists(path)) {
    LOGE("Fail to save the plot into the " << path << " file");
    return false;
  }

  LOGD("The plot is saved into the " << path << " file");

  return true;
}

MatPlotxxControllerPtr MatPlotxxController::create()
{
  return std::make_shared<MatPlotxxController>();
}

}  // namespace matplotxxi
