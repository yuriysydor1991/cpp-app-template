#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_QT6INITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_QT6INITER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace Qt6i
{

/**
 * @brief The Qt6 application initialization and starter class.
 *
 * Creates the QGuiApplication instance required by the native Qt Vulkan
 * integration (QVulkanInstance lives in Qt6::Gui and needs the platform
 * integration) and drives the QtVulkanController that creates a Vulkan instance,
 * enumerates the available physical devices and logs their properties. No
 * GUI/QML window is shown.
 */
class Qt6Initer
{
 public:
  virtual ~Qt6Initer() = default;
  Qt6Initer() = default;

  /**
   * @brief Starts the Qt6 application: brings up a Vulkan instance through the
   * native Qt QVulkanInstance and logs the available physical devices.
   *
   * @param actx The application context with all the necessary info.
   *
   * @return Should return the application return status.
   * Zero at success and non-zero value otherwise.
   */
  virtual int run(std::shared_ptr<app::ApplicationContext> actx);
};

}  // namespace Qt6i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_QT6INITER_CLASS_H
