#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <functional>
#include <string>

#include "src/gdbus/query-handlers/Hostname1QueryHandler.h"

namespace Gio
{
namespace DBus
{
class Connection;
}  // namespace DBus
}  // namespace Gio

using namespace testing;
using namespace gdbusi;

namespace
{

/**
 * @brief A non-null, opaque connection pointer.
 *
 * It is never dereferenced because the fetch_properties() seam is overridden in
 * the test double below, so a real Gio::DBus::Connection (which would require a
 * live bus and Gio::init()) is not needed to drive handle().
 */
Gio::DBus::Connection* fake_connection()
{
  static int placeholder{0};
  return reinterpret_cast<Gio::DBus::Connection*>(&placeholder);
}

/**
 * @brief Test double that replaces the only bus-touching method with a
 * configurable callback, so the handle() orchestration (and its LOGI logging)
 * can be exercised in isolation, without a live D-Bus.
 */
class TestableHostname1QueryHandler : public Hostname1QueryHandler
{
 public:
  using Hostname1QueryHandler::Hostname1Properties;

  std::function<bool(Gio::DBus::Connection*, Hostname1Properties&, std::string&)>
      onFetch;

 protected:
  bool fetch_properties(Gio::DBus::Connection* connection,
                        Hostname1Properties& out, std::string& error) override
  {
    if (onFetch) {
      return onFetch(connection, out, error);
    }

    return false;
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
  Gio::DBus::Connection* received = nullptr;

  handler.onFetch =
      [&](Gio::DBus::Connection* connection,
          TestableHostname1QueryHandler::Hostname1Properties& out,
          std::string&) {
        received = connection;

        out.hostname = "unit-test-host";
        out.prettyHostname = "Unit Test Host";
        out.osPrettyName = "UnitTestOS 1.0";
        out.kernelName = "Linux";
        out.kernelRelease = "0.0.0-unit";
        out.chassis = "container";

        return true;
      };

  EXPECT_TRUE(handler.handle(fake_connection()));
  EXPECT_EQ(received, fake_connection());
}

TEST_F(UTEST_Hostname1QueryHandler, handle_returns_false_on_dbus_error)
{
  handler.onFetch =
      [&](Gio::DBus::Connection*,
          TestableHostname1QueryHandler::Hostname1Properties&,
          std::string& error) {
        error =
            "org.freedesktop.DBus.Error.ServiceUnknown: the name "
            "org.freedesktop.hostname1 was not provided by any .service files";
        return false;
      };

  EXPECT_FALSE(handler.handle(fake_connection()));
}

TEST_F(UTEST_Hostname1QueryHandler, handle_returns_false_on_null_connection)
{
  bool fetchCalled = false;

  handler.onFetch =
      [&](Gio::DBus::Connection*,
          TestableHostname1QueryHandler::Hostname1Properties&, std::string&) {
        fetchCalled = true;
        return true;
      };

  // Asserts are compiled out for the unit tests (NDEBUG), so the explicit
  // nullptr guard inside handle() is what is being exercised here.
  EXPECT_FALSE(handler.handle(nullptr));
  EXPECT_FALSE(fetchCalled);
}

TEST_F(UTEST_Hostname1QueryHandler, exposes_expected_well_known_coordinates)
{
  EXPECT_EQ(Hostname1QueryHandler::serviceName, "org.freedesktop.hostname1");
  EXPECT_EQ(Hostname1QueryHandler::objectPath, "/org/freedesktop/hostname1");
  EXPECT_EQ(Hostname1QueryHandler::interfaceName, "org.freedesktop.hostname1");
  EXPECT_EQ(Hostname1QueryHandler::hostnameProperty, "Hostname");
  EXPECT_EQ(Hostname1QueryHandler::prettyHostnameProperty, "PrettyHostname");
  EXPECT_EQ(Hostname1QueryHandler::osPrettyNameProperty,
            "OperatingSystemPrettyName");
}
