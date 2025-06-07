#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_QT6INITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_QT6INITER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace Qt6i
{

/**
 * @brief The Qt initialization and starter class.
 */
class Qt6Initer
{
 public:
  virtual ~Qt6Initer() = default;
  Qt6Initer() = default;

  /**
   * @brief Starts the Qt6 available application.
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
