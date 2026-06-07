#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4INITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4INITER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace Gtkmm4i
{

/**
 * @brief The GTKmm4 application initialization and starter class.
 *
 * Drives the headless Vulkan physical device enumeration (logging the device
 * properties through the application logger) and then brings up the GTK4
 * application showing a blank, black window for the lifetime of the GTK main
 * loop. GTK4 exposes no Vulkan rendering widget, so the Vulkan work and the
 * window are kept independent.
 */
class GtkmmIniter
{
 public:
  virtual ~GtkmmIniter() = default;
  GtkmmIniter() = default;

  /**
   * @brief Enumerates the Vulkan physical devices and starts the GTK4 window.
   *
   * @param nactx The application context with all the necessary info.
   *
   * @return Returns the application return status: zero on success and a
   * non-zero value otherwise.
   */
  virtual int run(std::shared_ptr<app::ApplicationContext> nactx);

 private:
  std::shared_ptr<app::ApplicationContext> actx;
};

}  // namespace Gtkmm4i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4INITER_CLASS_H
