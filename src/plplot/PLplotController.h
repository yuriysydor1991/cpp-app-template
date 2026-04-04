#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PLPLOTCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PLPLOTCONTROLLER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace plploti
{

/**
 * @brief The PLplot library interface controller class.
 */
class PLplotController
{
 public:
  using PLplotControllerPtr = std::shared_ptr<PLplotController>;

  virtual ~PLplotController() = default;
  PLplotController() = default;

  virtual bool run(std::shared_ptr<app::ApplicationContext> ctx);

  static PLplotControllerPtr create();

 private:
  bool draw_simple_plot();
};

using PLplotControllerPtr = PLplotController::PLplotControllerPtr;

}  // namespace plploti

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PLPLOTCONTROLLER_CLASS_H
