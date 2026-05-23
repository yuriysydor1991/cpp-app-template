#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include <sdbus-c++/sdbus-c++.h>

#include "src/app/ApplicationContext.h"
#include "src/sdbuscxx/SDBusCxxController.h"

using namespace testing;
using namespace sdbuscxxi;

class CTEST_SDBusCxxController : public Test
{
 public:
  CTEST_SDBusCxxController()
      : appCtx{std::make_shared<app::ApplicationContext>(argc, argv)}
  {
  }

  /**
   * @brief Whether a system bus connection can be opened in this environment.
   */
  static bool system_bus_reachable()
  {
    try {
      std::unique_ptr<sdbus::IConnection> probe =
          sdbus::createSystemBusConnection();
      return probe != nullptr;
    } catch (const sdbus::Error&) {
      return false;
    }
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<app::ApplicationContext> appCtx;
};

TEST_F(CTEST_SDBusCxxController, create_reflects_system_bus_availability)
{
  SDBusCxxControllerPtr controller = SDBusCxxController::create();

  if (system_bus_reachable()) {
    EXPECT_NE(controller, nullptr);
  } else {
    // init() catches the connection error, so create() reports the failure by
    // returning an empty pointer instead of a half-constructed controller.
    EXPECT_EQ(controller, nullptr);
  }
}

TEST_F(CTEST_SDBusCxxController, run_against_live_system_bus)
{
  if (!system_bus_reachable()) {
    GTEST_SKIP() << "System bus is not reachable in this environment";
  }

  SDBusCxxControllerPtr controller = SDBusCxxController::create();

  ASSERT_NE(controller, nullptr);

  // The demo call reads read-only properties from hostname1 (systemd-hostnamed),
  // a standard bus-activatable system service, so on a host that exposes a
  // system bus run() must complete successfully.
  EXPECT_TRUE(controller->run(appCtx));
}
