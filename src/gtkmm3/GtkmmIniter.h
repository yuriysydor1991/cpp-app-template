#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMINITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMINITER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/gtkmm3/main-window/Loader.h"

namespace Gtkmm3i
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

 protected:
  virtual bool create_main_window_loader();
  virtual bool prepare_main_window();

  std::shared_ptr<app::ApplicationContext> actx;

  main_window::LoaderPtr loader;
};

}  // namespace Gtkmm3i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMINITER_CLASS_H
