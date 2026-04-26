#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <functional>
#include <string>

#include <sdbus-c++/sdbus-c++.h>

#include "src/sdbuscxx/query-handlers/Hostname1QueryHandler.h"

using namespace testing;
using namespace sdbuscxxi;

namespace
{

/**
 * @brief A non-null, opaque connection pointer.
 *
 * It is never dereferenced because the fetch_properties() seam is overridden in
 * the test double below, so a real sdbus::IConnection instance (which would
 * require a live bus) is not needed to drive handle().
 */
sdbus::IConnection* fake_connection()
{
  static int placeholder{0};
  return reinterpret_cast<sdbus::IConnection*>(&placeholder);
}

/**
 * @brief Test double that replaces the only bus-touching method with a
 * configurable callback, so the handle() orchestration can be exercised in
 * isolation, without a live D-Bus.
 */
class TestableHostname1QueryHandler : public Hostname1QueryHandler
{
 public:
  // Re-export the protected result type so the test bodies can name it.
  using Hostname1QueryHandler::Hostname1Properties;

  std::function<Hostname1Properties(sdbus::IConnection*)> onFetchProperties;

 protected:
  Hostname1Properties fetch_properties(sdbus::IConnection* connection) override
  {
    if (onFetchProperties) {
      return onFetchProperties(connection);
    }

    return {};
  }
};

}  // namespace

class UTEST_Hostname1QueryHandler : public Test
{
 public:
  TestableHostname1QueryHandler handler;
};

TEST_F(UTEST_Hostname1QueryHandler, handle_returns_true_on_successful_fetch)
{
  sdbus::IConnection* received = nullptr;

  handler.onFetchProperties = [&](sdbus::IConnection* connection) {
    received = connection;

    TestableHostname1QueryHandler::Hostname1Properties props;
    props.hostname = "unit-test-host";
    props.prettyHostname = "Unit Test Host";
    props.osPrettyName = "UnitTestOS 1.0";

    return props;
  };

  EXPECT_TRUE(handler.handle(fake_connection()));
  EXPECT_EQ(received, fake_connection());
}

TEST_F(UTEST_Hostname1QueryHandler, handle_returns_false_on_dbus_error)
{
  handler.onFetchProperties =
      [&](sdbus::IConnection*)
      -> TestableHostname1QueryHandler::Hostname1Properties {
    throw sdbus::Error(
        sdbus::Error::Name{"org.freedesktop.DBus.Error.ServiceUnknown"},
        "The name org.freedesktop.hostname1 was not provided by any .service "
        "files");
  };

  EXPECT_FALSE(handler.handle(fake_connection()));
}

TEST_F(UTEST_Hostname1QueryHandler, handle_returns_false_on_null_connection)
{
  bool fetchCalled = false;

  handler.onFetchProperties = [&](sdbus::IConnection*) {
    fetchCalled = true;
    return TestableHostname1QueryHandler::Hostname1Properties{};
  };

  // Asserts are compiled out for the unit tests (NDEBUG), so the explicit
  // nullptr guard inside handle() is what is being exercised here.
  EXPECT_FALSE(handler.handle(nullptr));
  EXPECT_FALSE(fetchCalled);
}

TEST_F(UTEST_Hostname1QueryHandler, exposes_expected_well_known_coordinates)
{
  EXPECT_EQ(static_cast<std::string>(Hostname1QueryHandler::serviceName),
            "org.freedesktop.hostname1");
  EXPECT_EQ(static_cast<std::string>(Hostname1QueryHandler::objectPath),
            "/org/freedesktop/hostname1");
  EXPECT_EQ(static_cast<std::string>(Hostname1QueryHandler::interfaceName),
            "org.freedesktop.hostname1");
  EXPECT_EQ(static_cast<std::string>(Hostname1QueryHandler::hostnameProperty),
            "Hostname");
  EXPECT_EQ(
      static_cast<std::string>(Hostname1QueryHandler::prettyHostnameProperty),
      "PrettyHostname");
  EXPECT_EQ(
      static_cast<std::string>(Hostname1QueryHandler::osPrettyNameProperty),
      "OperatingSystemPrettyName");
}
