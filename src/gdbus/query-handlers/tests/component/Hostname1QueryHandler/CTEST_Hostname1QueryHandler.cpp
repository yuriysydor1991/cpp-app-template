#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include <giomm/dbusconnection.h>
#include <giomm/init.h>
#include <glibmm/error.h>
#include <glibmm/refptr.h>

#include "src/gdbus/query-handlers/DBusQueryHandlerFactory.h"
#include "src/gdbus/query-handlers/Hostname1QueryHandler.h"
#include "src/gdbus/query-handlers/IDBusQueryHandler.h"

using namespace testing;
using namespace gdbusi;

class CTEST_Hostname1QueryHandler : public Test
{
 public:
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

  DBusQueryHandlerFactory factory;
};

TEST_F(CTEST_Hostname1QueryHandler, factory_creates_non_null_default_handler)
{
  IDBusQueryHandlerPtr handler = factory.create_default_handler();

  EXPECT_NE(handler, nullptr);
}

TEST_F(CTEST_Hostname1QueryHandler, factory_default_handler_is_hostname1)
{
  IDBusQueryHandlerPtr handler = factory.create_default_handler();

  EXPECT_NE(std::dynamic_pointer_cast<Hostname1QueryHandler>(handler), nullptr);
}

TEST_F(CTEST_Hostname1QueryHandler, live_system_bus_query)
{
  if (!system_bus_reachable()) {
    GTEST_SKIP() << "System bus is not reachable in this environment";
  }

  Glib::RefPtr<Gio::DBus::Connection> bus =
      Gio::DBus::Connection::get_sync(Gio::DBus::BusType::SYSTEM);

  IDBusQueryHandlerPtr handler = factory.create_default_handler();

  ASSERT_NE(handler, nullptr);

  // hostname1 (systemd-hostnamed) is a standard, bus-activatable system
  // service; on a host that exposes a system bus the read-only properties are
  // retrievable without elevated privileges and get logged.
  EXPECT_TRUE(handler->handle(bus.get()));
}

int main(int argc, char** argv)
{
  Gio::init();
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
