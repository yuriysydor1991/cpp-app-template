#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4CONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4CONTROLLER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace Gtkmm4i
{

/**
 * @brief Creates the GTK4 application and runs the main window in it until
 * the window is closed or the application stop is requested.
 */
class Gtkmm4Controller
{
 public:
  virtual ~Gtkmm4Controller() = default;
  Gtkmm4Controller() = default;

  virtual int run(std::shared_ptr<app::ApplicationContext> nactx);

 private:
  std::shared_ptr<app::ApplicationContext> actx;
};

}  // namespace Gtkmm4i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4CONTROLLER_CLASS_H
