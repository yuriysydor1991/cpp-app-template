#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include <giomm/dbusconnection.h>

#include "src/gdbus/GDBusController.h"
#include "src/gdbus/query-handlers/DBusQueryHandlerFactory.h"
#include "src/gdbus/query-handlers/IDBusQueryHandler.h"

using namespace testing;
using namespace gdbusi;

namespace
{

/**
 * @brief Test double exposing the protected seams so run()'s orchestration may
 * be exercised without a live system bus: inited() is forced true and the
 * connection pointer handed to the (mocked) handler is an unused nullptr.
 */
class TestableGDBusController : public GDBusController
{
 protected:
  bool init() override { return true; }
  bool inited() const override { return true; }
  Gio::DBus::Connection* connection_ptr() override { return nullptr; }
};

}  // namespace

class UTEST_GDBusController : public Test
{
 public:
  UTEST_GDBusController()
      : handler{std::make_shared<NiceMock<IDBusQueryHandler>>()}
  {
    // The controller builds a DBusQueryHandlerFactory internally; route every
    // created factory to hand out the fixture's mock handler.
    DBusQueryHandlerFactory::onMockCreate = [this](DBusQueryHandlerFactory& f) {
      EXPECT_CALL(f, create_default_handler()).WillRepeatedly(Return(handler));
    };
  }

  ~UTEST_GDBusController() override
  {
    DBusQueryHandlerFactory::onMockCreate = nullptr;
  }

  std::shared_ptr<NiceMock<IDBusQueryHandler>> handler;
};

TEST_F(UTEST_GDBusController, run_returns_false_when_not_initialized)
{
  // A controller built directly (not through create()) holds no connection, so
  // inited() is false and run() bails out before the query call.
  GDBusController controller;

  EXPECT_FALSE(controller.run());
}

TEST_F(UTEST_GDBusController, run_succeeds_when_query_handler_succeeds)
{
  ON_CALL(*handler, handle(_)).WillByDefault(Return(true));

  TestableGDBusController controller;

  EXPECT_TRUE(controller.run());
}

TEST_F(UTEST_GDBusController, run_returns_false_when_query_handler_fails)
{
  ON_CALL(*handler, handle(_)).WillByDefault(Return(false));

  TestableGDBusController controller;

  EXPECT_FALSE(controller.run());
}
