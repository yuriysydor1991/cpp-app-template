#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QDBusConnection>

#include "src/qtdbus/QtDBusController.h"
#include "src/qtdbus/SystemInformation.h"

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

  SystemInformation info;
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
  // service, so on a host that exposes a system bus run() must complete and the
  // mandatory Hostname property must come back non-empty.
  EXPECT_TRUE(controller->run(info));
  EXPECT_FALSE(info.hostname.isEmpty());
}

int main(int argc, char** argv)
{
  QCoreApplication app(argc, argv);
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
