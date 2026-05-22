#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SDBUSCXXCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SDBUSCXXCONTROLLER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace sdbuscxxi
{

/**
 * @brief A header-only stub of the real SDBusCxxController for the app facade
 * component test.
 *
 * The real controller starts a blocking D-Bus server and pulls in sdbus-c++.
 * The app facade component test only needs a controller that constructs and
 * reports success, so it stubs it here - the same way the test stubs the
 * logger - keeping CTEST_app free of a live bus and of the sdbus-c++ link.
 */
class SDBusCxxController
{
 public:
  using SDBusCxxControllerPtr = std::shared_ptr<SDBusCxxController>;

  virtual ~SDBusCxxController() = default;
  SDBusCxxController() = default;

  virtual bool run(std::shared_ptr<app::ApplicationContext> /*ctx*/)
  {
    return true;
  }

  static SDBusCxxControllerPtr create()
  {
    return std::make_shared<SDBusCxxController>();
  }
};

using SDBusCxxControllerPtr = SDBusCxxController::SDBusCxxControllerPtr;

}  // namespace sdbuscxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SDBUSCXXCONTROLLER_CLASS_H
