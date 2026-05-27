#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QDBusConnection>

#include "src/qtdbus/QtDBusController.h"

using namespace testing;
using namespace qtdbusi;

class CTEST_QtDBusController : public Test
{
 public:
  /**
   * @brief Whether a system bus connection can be opened in this environment.
   */
  static bool system_bus_reachable()
  {
    return QDBusConnection::systemBus().isConnected();
  }
};

TEST_F(CTEST_QtDBusController, create_reflects_system_bus_availability)
{
  QtDBusControllerPtr controller = QtDBusController::create();

  if (system_bus_reachable()) {
    EXPECT_NE(controller, nullptr);
  } else {
    // init() reports the unreachable bus, so create() returns an empty pointer
    // instead of a half-constructed controller.
    EXPECT_EQ(controller, nullptr);
  }
}

TEST_F(CTEST_QtDBusController, run_against_live_system_bus)
{
  if (!system_bus_reachable()) {
    GTEST_SKIP() << "System bus is not reachable in this environment";
  }

  QtDBusControllerPtr controller = QtDBusController::create();

  ASSERT_NE(controller, nullptr);

  // hostname1 (systemd-hostnamed) is a standard, bus-activatable system
  // service, so on a host that exposes a system bus run() reads its read-only
  // properties, logs them and completes successfully.
  EXPECT_TRUE(controller->run());
}

int main(int argc, char** argv)
{
  QCoreApplication app(argc, argv);
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
