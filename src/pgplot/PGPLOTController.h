#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PGPLOTCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PGPLOTCONTROLLER_CLASS_H

#include <memory>

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

  virtual ~PGPLOTController() = default;
  PGPLOTController() = default;

  virtual bool run(std::shared_ptr<app::ApplicationContext> ctx);

  static PGPLOTControllerPtr create();

 private:
  bool draw_simple_plot();
};

using PGPLOTControllerPtr = PGPLOTController::PGPLOTControllerPtr;

}  // namespace pgploti

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PGPLOTCONTROLLER_CLASS_H
