#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cctype>
#include <cstddef>
#include <memory>
#include <string>

#include <sdbus-c++/sdbus-c++.h>

#include "src/sdbuscxx/server-objects/CurrentDateServerObject.h"
#include "src/sdbuscxx/server-objects/DBusServerObjectFactory.h"
#include "src/sdbuscxx/server-objects/IDBusServerObject.h"

using namespace testing;
using namespace sdbuscxxi;

class CTEST_CurrentDateServerObject : public Test
{
 public:
  DBusServerObjectFactory factory;
};

TEST_F(CTEST_CurrentDateServerObject, factory_creates_non_null_default_object)
{
  EXPECT_NE(factory.create_default_object(), nullptr);
}

TEST_F(CTEST_CurrentDateServerObject, factory_default_object_is_current_date)
{
  IDBusServerObjectPtr object = factory.create_default_object();

  EXPECT_NE(std::dynamic_pointer_cast<CurrentDateServerObject>(object), nullptr);
}

TEST_F(CTEST_CurrentDateServerObject, served_current_date_roundtrip)
{
  std::unique_ptr<sdbus::IConnection> serverConn;

  try {
    serverConn = sdbus::createSessionBusConnection();
  } catch (const sdbus::Error& e) {
    GTEST_SKIP() << "Session bus is not reachable in this environment: ["
                 << static_cast<std::string>(e.getName()) << "] "
                 << e.getMessage();
  }

  ASSERT_NE(serverConn, nullptr);

  // Server side: export the default object and start serving asynchronously.
  IDBusServerObjectPtr serverObject = factory.create_default_object();
  ASSERT_NE(serverObject, nullptr);

  std::unique_ptr<sdbus::IObject> object =
      sdbus::createObject(*serverConn, serverObject->object_path());
  serverObject->register_on(*object);
  serverConn->requestName(serverObject->service_name());
  serverConn->enterEventLoopAsync();

  // Client side: a separate connection reads the CurrentDate property back.
  std::unique_ptr<sdbus::IConnection> clientConn =
      sdbus::createSessionBusConnection();
  std::unique_ptr<sdbus::IProxy> proxy = sdbus::createProxy(
      *clientConn, serverObject->service_name(), serverObject->object_path());

  const std::string served =
      proxy->getProperty(CurrentDateServerObject::currentDateProperty)
          .onInterface(CurrentDateServerObject::interfaceName)
          .get<std::string>();

  serverConn->leaveEventLoop();

  // The value served over the bus must be a well formed YYYY-MM-DD date.
  ASSERT_EQ(served.size(), 10U);
  EXPECT_EQ(served[4], '-');
  EXPECT_EQ(served[7], '-');
  for (std::size_t i : {0U, 1U, 2U, 3U, 5U, 6U, 8U, 9U}) {
    EXPECT_TRUE(std::isdigit(static_cast<unsigned char>(served[i])));
  }
}
