#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include <sdbus-c++/sdbus-c++.h>

#include "src/app/ApplicationContext.h"
#include "src/sdbuscxx/SDBusCxxController.h"
#include "src/sdbuscxx/query-handlers/DBusQueryHandlerFactory.h"
#include "src/sdbuscxx/query-handlers/IDBusQueryHandler.h"

using namespace testing;
using namespace sdbuscxxi;

class UTEST_SDBusCxxController : public Test
{
 public:
  UTEST_SDBusCxxController()
      : appCtx{std::make_shared<app::ApplicationContext>(argc, argv)},
        handler{std::make_shared<NiceMock<IDBusQueryHandler>>()}
  {
    // The controller builds a DBusQueryHandlerFactory internally; route every
    // created factory to hand out the fixture's mock handler.
    DBusQueryHandlerFactory::onMockCreate = [this](DBusQueryHandlerFactory& f) {
      EXPECT_CALL(f, create_default_handler()).WillRepeatedly(Return(handler));
    };
    sdbus::mock::fail_bus_connection() = false;
  }

  ~UTEST_SDBusCxxController() override
  {
    DBusQueryHandlerFactory::onMockCreate = nullptr;
    sdbus::mock::fail_bus_connection() = false;
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<app::ApplicationContext> appCtx;
  std::shared_ptr<NiceMock<IDBusQueryHandler>> handler;
};

TEST_F(UTEST_SDBusCxxController, run_returns_false_on_null_context)
{
  SDBusCxxController controller;

  // Asserts are compiled out for the unit tests (NDEBUG), so the explicit
  // nullptr guard inside run() is what is being exercised here.
  EXPECT_FALSE(controller.run(nullptr));
}

TEST_F(UTEST_SDBusCxxController, run_returns_false_when_not_initialized)
{
  // A controller built directly (not through create()) holds no connection, so
  // inited() is false and run() bails out before the demo call.
  SDBusCxxController controller;

  EXPECT_FALSE(controller.run(appCtx));
}

TEST_F(UTEST_SDBusCxxController, run_succeeds_when_query_handler_succeeds)
{
  ON_CALL(*handler, handle(_)).WillByDefault(Return(true));

  SDBusCxxControllerPtr controller = SDBusCxxController::create();

  ASSERT_NE(controller, nullptr);
  EXPECT_TRUE(controller->run(appCtx));
}

TEST_F(UTEST_SDBusCxxController, run_returns_false_when_query_handler_fails)
{
  ON_CALL(*handler, handle(_)).WillByDefault(Return(false));

  SDBusCxxControllerPtr controller = SDBusCxxController::create();

  ASSERT_NE(controller, nullptr);
  EXPECT_FALSE(controller->run(appCtx));
}

TEST_F(UTEST_SDBusCxxController, create_returns_null_when_bus_unavailable)
{
  sdbus::mock::fail_bus_connection() = true;

  EXPECT_EQ(SDBusCxxController::create(), nullptr);
}
