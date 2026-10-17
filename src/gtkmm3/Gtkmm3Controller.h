#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM3CONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM3CONTROLLER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace Gtkmm3i
{

/**
 * @brief Creates the GTK3 application and runs the main window in it until
 * the window is closed or the application stop is requested.
 */
class Gtkmm3Controller
{
 public:
  virtual ~Gtkmm3Controller() = default;
  Gtkmm3Controller() = default;

  virtual int run(std::shared_ptr<app::ApplicationContext> nactx);

 private:
  std::shared_ptr<app::ApplicationContext> actx;
};

}  // namespace Gtkmm3i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM3CONTROLLER_CLASS_H
