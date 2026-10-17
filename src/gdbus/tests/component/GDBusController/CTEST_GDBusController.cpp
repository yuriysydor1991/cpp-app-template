#include <giomm/dbusconnection.h>
#include <giomm/init.h>
#include <glibmm/error.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/gdbus/GDBusController.h"
#include "src/gdbus/query-handlers/Hostname1QueryHandler.h"

using namespace testing;
using namespace gdbusi;

class CTEST_GDBusController : public Test
{
 public:
  /**
   * @brief Whether a system bus connection can be opened in this environment.
   */
  static bool system_bus_reachable()
  {
    try {
      return static_cast<bool>(
          Gio::DBus::Connection::get_sync(Gio::DBus::BusType::SYSTEM));
    }
    catch (const Glib::Error&) {
      return false;
    }
  }

  /**
   * @brief Whether the hostname1 service answers on the system bus. A system
   * bus without the systemd-hostnamed (a container, a non systemd host) skips
   * the live cases instead of failing them.
   */
  static bool hostnamed_reachable()
  {
    try {
      const auto bus =
          Gio::DBus::Connection::get_sync(Gio::DBus::BusType::SYSTEM);

      if (!bus) {
        return false;
      }

      bus->call_sync(Hostname1QueryHandler::objectPath,
                     "org.freedesktop.DBus.Peer", "Ping",
                     Glib::VariantContainerBase{},
                     Hostname1QueryHandler::serviceName);

      return true;
    }
    catch (const Glib::Error&) {
      return false;
    }
  }
};

TEST_F(CTEST_GDBusController, create_reflects_system_bus_availability)
{
  GDBusControllerPtr controller = GDBusController::create();

  if (system_bus_reachable()) {
    EXPECT_NE(controller, nullptr);
  } else {
    // init() reports the unreachable bus, so create() returns an empty pointer
    // instead of a half-constructed controller.
    EXPECT_EQ(controller, nullptr);
  }
}

TEST_F(CTEST_GDBusController, run_against_live_system_bus)
{
  if (!hostnamed_reachable()) {
    GTEST_SKIP()
        << "The hostname1 service is not reachable in this environment";
  }

  GDBusControllerPtr controller = GDBusController::create();

  ASSERT_NE(controller, nullptr);

  // hostname1 (systemd-hostnamed) is a standard, bus-activatable system
  // service, so on a host that exposes a system bus run() reads its read-only
  // properties, logs them and completes successfully.
  EXPECT_TRUE(controller->run());
}

int main(int argc, char* argv[])
{
  Gio::init();
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
