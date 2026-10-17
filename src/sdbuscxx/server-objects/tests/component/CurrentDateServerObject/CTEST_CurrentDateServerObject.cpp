#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cctype>
#include <cstddef>
#include <memory>
#include <string>

#include "src/sdbuscxx/sdbuscxx-includes.h"
#include "src/sdbuscxx/server-objects/CurrentDateServerObject.h"
#include "src/sdbuscxx/server-objects/DBusServerObjectFactory.h"
#include "src/sdbuscxx/server-objects/IDBusServerObject.h"

using namespace testing;
using namespace sdbuscxxi;

class CTEST_CurrentDateServerObject : public Test
{
 public:
  /// @brief Asks the bus daemon whether the given name has an owner.
  static bool name_owned(sdbus::IConnection& connection,
                         const sdbus::ServiceName& name)
  {
    auto daemon = sdbus::createProxy(
        connection, sdbus::ServiceName{"org.freedesktop.DBus"},
        sdbus::ObjectPath{"/org/freedesktop/DBus"});

    bool owned{false};

    daemon->callMethod("NameHasOwner")
        .onInterface("org.freedesktop.DBus")
        .withArguments(static_cast<std::string>(name))
        .storeResultsTo(owned);

    return owned;
  }

  DBusServerObjectFactory factory;
};

TEST_F(CTEST_CurrentDateServerObject, served_current_date_roundtrip)
{
  std::unique_ptr<sdbus::IConnection> serverConn;

  try {
    serverConn = sdbus::createSessionBusConnection();
  }
  catch (const sdbus::Error& e) {
    GTEST_SKIP() << "Session bus is not reachable in this environment: ["
                 << static_cast<std::string>(e.getName()) << "] "
                 << e.getMessage();
  }

  ASSERT_NE(serverConn, nullptr);

  // Server side: export the default object and start serving asynchronously.
  IDBusServerObjectPtr serverObject = factory.create_default_object();
  ASSERT_NE(serverObject, nullptr);

  // A server instance running already owns the name, which the test may not
  // take over from it.
  if (name_owned(*serverConn, serverObject->service_name())) {
    GTEST_SKIP() << "The " << serverObject->service_name()
                 << " name is owned by a running server already";
  }

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
