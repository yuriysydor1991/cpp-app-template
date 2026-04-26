#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include <sdbus-c++/sdbus-c++.h>

#include "src/sdbuscxx/query-handlers/DBusQueryHandlerFactory.h"
#include "src/sdbuscxx/query-handlers/Hostname1QueryHandler.h"
#include "src/sdbuscxx/query-handlers/IDBusQueryHandler.h"

using namespace testing;
using namespace sdbuscxxi;

class CTEST_Hostname1QueryHandler : public Test
{
 public:
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

TEST_F(CTEST_Hostname1QueryHandler, exposes_expected_well_known_coordinates)
{
  EXPECT_EQ(static_cast<std::string>(Hostname1QueryHandler::serviceName),
            "org.freedesktop.hostname1");
  EXPECT_EQ(static_cast<std::string>(Hostname1QueryHandler::objectPath),
            "/org/freedesktop/hostname1");
  EXPECT_EQ(static_cast<std::string>(Hostname1QueryHandler::interfaceName),
            "org.freedesktop.hostname1");
}

TEST_F(CTEST_Hostname1QueryHandler, live_system_bus_query)
{
  std::unique_ptr<sdbus::IConnection> conn;

  try {
    conn = sdbus::createSystemBusConnection();
  } catch (const sdbus::Error& e) {
    GTEST_SKIP() << "System bus is not reachable in this environment: ["
                 << static_cast<std::string>(e.getName()) << "] "
                 << e.getMessage();
  }

  ASSERT_NE(conn, nullptr);

  IDBusQueryHandlerPtr handler = factory.create_default_handler();

  ASSERT_NE(handler, nullptr);

  // hostname1 (systemd-hostnamed) is a standard, bus-activatable system
  // service; on a host that exposes a system bus the read-only properties must
  // be retrievable without elevated privileges.
  EXPECT_TRUE(handler->handle(conn.get()));
}
