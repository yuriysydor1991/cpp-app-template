#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_QT6CONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_QT6CONTROLLER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace Qt6i
{

/**
 * @brief The Qt6 application initialization and starter class.
 *
 * Creates the QCoreApplication instance required by the Qt D-Bus module and
 * drives the QtDBusController that reads the general system information and
 * logs it. No GUI/QML is involved.
 */
class Qt6Controller
{
 public:
  virtual ~Qt6Controller() = default;
  Qt6Controller() = default;

  /**
   * @brief Starts the Qt6 application: reads and logs the general system
   * information over the system D-Bus.
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
