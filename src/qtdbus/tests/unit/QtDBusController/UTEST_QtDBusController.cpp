#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <QDBusConnection>
#include <memory>

#include "src/qtdbus/QtDBusController.h"
#include "src/qtdbus/query-handlers/DBusQueryHandlerFactory.h"
#include "src/qtdbus/query-handlers/IDBusQueryHandler.h"
#include "src/qtdbus/tests/unit/QtDBusController/TestableQtDBusController.h"

using namespace testing;
using namespace qtdbusi;

class UTEST_QtDBusController : public Test
{
 public:
  UTEST_QtDBusController()
      : handler{std::make_shared<NiceMock<IDBusQueryHandler>>()}
  {
    // The controller builds a DBusQueryHandlerFactory internally; route every
    // created factory to hand out the fixture's mock handler.
    DBusQueryHandlerFactory::onMockCreate = [this](DBusQueryHandlerFactory& f) {
      EXPECT_CALL(f, create_default_handler()).WillRepeatedly(Return(handler));
    };
  }

  ~UTEST_QtDBusController() override
  {
    DBusQueryHandlerFactory::onMockCreate = nullptr;
  }

  std::shared_ptr<NiceMock<IDBusQueryHandler>> handler;
};

TEST_F(UTEST_QtDBusController, run_returns_false_when_not_initialized)
{
  // A controller built directly (not through create()) holds no connection, so
  // inited() is false and run() bails out before the query call.
  QtDBusController controller;

  EXPECT_FALSE(controller.run());
}

TEST_F(UTEST_QtDBusController, run_succeeds_when_query_handler_succeeds)
{
  ON_CALL(*handler, handle(_)).WillByDefault(Return(true));

  TestableQtDBusController controller;

  EXPECT_TRUE(controller.run());
}

TEST_F(UTEST_QtDBusController, run_returns_false_when_query_handler_fails)
{
  ON_CALL(*handler, handle(_)).WillByDefault(Return(false));

  TestableQtDBusController controller;

  EXPECT_FALSE(controller.run());
}
