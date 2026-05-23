#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SDBUSCXXCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SDBUSCXXCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace sdbuscxxi
{

/**
 * @brief A header-only GTest/GMock mock of the real SDBusCxxController used by
 * the app component tests.
 *
 * The real controller pulls in sdbus-c++ and opens a live D-Bus connection,
 * neither of which is available to the app tests. Application obtains its
 * controller solely through the static create() factory, so the mock keeps an
 * onMockCreate seam (the same idiom as the Application mock) that a test sets
 * to hand out a pre-configured instance - or an empty pointer to emulate a
 * creation failure. The run() interaction is a regular mocked method whose
 * behaviour and invocations can be asserted.
 */
class SDBusCxxController
{
 public:
  using SDBusCxxControllerPtr = std::shared_ptr<SDBusCxxController>;

  virtual ~SDBusCxxController() = default;
  SDBusCxxController() = default;

  MOCK_METHOD(bool, run, (std::shared_ptr<app::ApplicationContext> ctx));

  /// @brief Test seam consulted by create(); see the class description.
  inline static std::function<SDBusCxxControllerPtr()> onMockCreate;

  static SDBusCxxControllerPtr create()
  {
    if (onMockCreate) {
      return onMockCreate();
    }

    return std::make_shared<SDBusCxxController>();
  }
};

using SDBusCxxControllerPtr = SDBusCxxController::SDBusCxxControllerPtr;

}  // namespace sdbuscxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SDBUSCXXCONTROLLER_CLASS_H
