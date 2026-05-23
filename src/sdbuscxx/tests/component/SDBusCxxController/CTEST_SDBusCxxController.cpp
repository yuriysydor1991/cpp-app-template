#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include <sdbus-c++/sdbus-c++.h>

#include "src/sdbuscxx/SDBusCxxController.h"

using namespace testing;
using namespace sdbuscxxi;

class CTEST_SDBusCxxController : public Test
{
 public:
  /**
   * @brief Whether a session bus connection can be opened in this environment.
   */
  static bool session_bus_reachable()
  {
    try {
      std::unique_ptr<sdbus::IConnection> probe =
          sdbus::createSessionBusConnection();
      return probe != nullptr;
    } catch (const sdbus::Error&) {
      return false;
    }
  }
};

TEST_F(CTEST_SDBusCxxController, create_reflects_session_bus_availability)
{
  const bool reachable = session_bus_reachable();

  // The server connects to the session bus during init(). run() itself is not
  // exercised here because it would block in the bus event loop until the
  // connection leaves it; the served round trip is covered by the server
  // object component test instead.
  SDBusCxxControllerPtr controller = SDBusCxxController::create();

  if (reachable) {
    EXPECT_NE(controller, nullptr);
  } else {
    // init() catches the connection error, so create() reports the failure by
    // returning an empty pointer instead of a half-constructed controller.
    EXPECT_EQ(controller, nullptr);
  }
}
