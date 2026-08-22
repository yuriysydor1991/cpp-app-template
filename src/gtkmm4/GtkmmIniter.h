#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4INITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4INITER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/gtkmm4/main-window/AdwaitaWindow.h"

namespace Gtkmm4i
{

/**
 * @brief Creates the GTK4 application instance, initializes the libadwaita
 * and runs the libadwaita main window.
 */
class GtkmmIniter
{
 public:
  virtual ~GtkmmIniter() = default;
  GtkmmIniter() = default;

  virtual int run(std::shared_ptr<app::ApplicationContext> nactx);

  /**
   * @brief Instantiates the libadwaita main window.
   *
   * @return Returns the created window instance.
   */
  static main_window::AdwaitaWindowPtr create_main_window();

 private:
  std::shared_ptr<app::ApplicationContext> actx;
};

}  // namespace Gtkmm4i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4INITER_CLASS_H
