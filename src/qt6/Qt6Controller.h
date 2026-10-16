#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_QT6CONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_QT6CONTROLLER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace Qt6i
{

/**
 * @brief The Qt6 application initialization and starter class.
 *
 * Creates the QApplication instance required by the native Qt Vulkan
 * integration (QVulkanInstance lives in Qt6::Gui and needs the platform
 * integration) and drives the QtVulkanController that creates a Vulkan
 * instance, enumerates the available physical devices and logs their
 * properties. The same instance then backs a blank, black, Vulkan rendered
 * window (BlankVulkanWindow) hosted in a top level QWidget (Qt6::Widgets) and
 * shown for the lifetime of the Qt event loop.
 */
class Qt6Controller
{
 public:
  virtual ~Qt6Controller() = default;
  Qt6Controller() = default;

  /**
   * @brief Starts the Qt6 application: brings up a Vulkan instance through the
   * native Qt QVulkanInstance, logs the available physical devices, shows a
   * blank black Vulkan window and runs the Qt event loop.
   *
   * @param actx The application context with all the necessary info.
   *
   * @return Should return the application return status.
   * Zero at success and non-zero value otherwise.
   */
  virtual int run(std::shared_ptr<app::ApplicationContext> actx);
};

}  // namespace Qt6i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_QT6CONTROLLER_CLASS_H
