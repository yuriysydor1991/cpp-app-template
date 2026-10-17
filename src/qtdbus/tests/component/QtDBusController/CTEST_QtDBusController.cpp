#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusMessage>

#include "src/qtdbus/QtDBusController.h"
#include "src/qtdbus/query-handlers/Hostname1QueryHandler.h"

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

  /**
   * @brief Whether the hostname1 service answers on the system bus. A system
   * bus without the systemd-hostnamed (a container, a non systemd host) skips
   * the live cases instead of failing them.
   */
  static bool hostnamed_reachable()
  {
    if (!system_bus_reachable()) {
      return false;
    }

    QDBusMessage ping = QDBusMessage::createMethodCall(
        Hostname1QueryHandler::serviceName, Hostname1QueryHandler::objectPath,
        "org.freedesktop.DBus.Peer", "Ping");

    return QDBusConnection::systemBus().call(ping).type() !=
           QDBusMessage::ErrorMessage;
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
  if (!hostnamed_reachable()) {
    GTEST_SKIP()
        << "The hostname1 service is not reachable in this environment";
  }

  QtDBusControllerPtr controller = QtDBusController::create();

  ASSERT_NE(controller, nullptr);

  // hostname1 (systemd-hostnamed) is a standard, bus-activatable system
  // service, so on a host that exposes a system bus run() reads its read-only
  // properties, logs them and completes successfully.
  EXPECT_TRUE(controller->run());
}

int main(int argc, char* argv[])
{
  QCoreApplication app(argc, argv);
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
