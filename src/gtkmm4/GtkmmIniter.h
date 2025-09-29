#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4INITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4INITER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace Gtkmm4i
{

/**
 * @brief The root GTKmm window class to show
 * templated GUI window.
 */
class GtkmmIniter
{
 public:
  virtual ~GtkmmIniter() = default;
  GtkmmIniter() = default;

  virtual int run(std::shared_ptr<app::ApplicationContext> nactx);

 private:
  std::shared_ptr<app::ApplicationContext> actx;
};

}  // namespace Gtkmm4i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4INITER_CLASS_H
