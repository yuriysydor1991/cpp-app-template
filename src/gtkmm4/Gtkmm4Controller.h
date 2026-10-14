#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4CONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4CONTROLLER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace Gtkmm4i
{

/**
 * @brief The root GTKmm window class to show
 * templated GUI window.
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
