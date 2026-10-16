#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PGPLOTCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PGPLOTCONTROLLER_CLASS_H

#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"

namespace pgploti
{

/**
 * @brief The PGPLOT library interface controller class.
 */
class PGPLOTController
{
 public:
  using PGPLOTControllerPtr = std::shared_ptr<PGPLOTController>;

  /// @brief The interactive X11 window device the plots are drawn onto by
  /// default.
  inline static constexpr const char* const DEFAULT_DEVICE = "/XWINDOW";

  virtual ~PGPLOTController() = default;

  /**
   * @param device The PGPLOT device to draw the plots onto: the DEFAULT_DEVICE
   * window or any other one supported by your PGPLOT installation ("/PNG",
   * "/PS", "/SVG", "/NULL", "plot.svg/SVG" and so on) to store the plots into
   * a file instead.
   */
  explicit PGPLOTController(std::string device = DEFAULT_DEVICE);

  virtual bool run(std::shared_ptr<app::ApplicationContext> ctx);

  static PGPLOTControllerPtr create();

 private:
  bool draw_simple_plot();

  const std::string plotDevice;
};

using PGPLOTControllerPtr = PGPLOTController::PGPLOTControllerPtr;

}  // namespace pgploti

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PGPLOTCONTROLLER_CLASS_H
