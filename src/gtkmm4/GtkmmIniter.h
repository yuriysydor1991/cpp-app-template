#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4INITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4INITER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace Gtkmm4i
{

/**
 * @brief The gtkmm4 application initialization and starter class.
 *
 * Initializes the giomm/GLib runtime required by the Gio::DBus module and
 * drives the GDBusController that reads the general system information and logs
 * it. No GUI window is involved.
 */
class GtkmmIniter
{
 public:
  virtual ~GtkmmIniter() = default;
  GtkmmIniter() = default;

  /**
   * @brief Starts the gtkmm4 application: reads and logs the general system
   * information over the system D-Bus.
   *
   * @param nactx The application context with all the necessary info.
   *
   * @return Should return the application return status.
   * Zero at success and non-zero value otherwise.
   */
  virtual int run(std::shared_ptr<app::ApplicationContext> nactx);
};

}  // namespace Gtkmm4i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4INITER_CLASS_H
