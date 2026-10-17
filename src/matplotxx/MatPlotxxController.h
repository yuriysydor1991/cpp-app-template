#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MATPLOTXXCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MATPLOTXXCONTROLLER_CLASS_H

#include <chrono>
#include <memory>
#include <string>

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

  /**
   * @brief Shows the example plot in a gnuplot window until the ENTER key is
   * pressed or the application is asked to stop (see the
   * app::ApplicationContext::get_stop accessor).
   *
   * @param ctx The application context to watch the stop flag of.
   *
   * @return Returns true when the plot got shown.
   */
  virtual bool run(std::shared_ptr<app::ApplicationContext> ctx);

  /**
   * @brief Draws the example plot into the given image file, the format of
   * which the gnuplot picks by the file extension (.svg, .png, .pdf etc.).
   *
   * @param path The image file to write.
   *
   * @return Returns true when the file got written.
   */
  virtual bool save(const std::string& path);

  static MatPlotxxControllerPtr create();

 private:
  /**
   * @brief Waits for the ENTER key until the application is asked to stop.
   *
   * @param ctx The application context to watch the stop flag of.
   */
  static void wait_for_enter_or_stop(
      const std::shared_ptr<app::ApplicationContext>& ctx);

  /// @brief How often the shown plot checks the application stop flag.
  inline static constexpr const std::chrono::milliseconds STOP_CHECK_PERIOD{
      100};
};

using MatPlotxxControllerPtr = MatPlotxxController::MatPlotxxControllerPtr;

}  // namespace matplotxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MATPLOTXXCONTROLLER_CLASS_H
