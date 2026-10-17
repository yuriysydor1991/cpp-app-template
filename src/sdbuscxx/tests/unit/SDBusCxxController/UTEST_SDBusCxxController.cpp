#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <memory>
#include <thread>

#include "src/app/ApplicationContext.h"
#include "src/sdbuscxx/SDBusCxxController.h"
#include "src/sdbuscxx/sdbuscxx-includes.h"
#include "src/sdbuscxx/server-objects/DBusServerObjectFactory.h"
#include "src/sdbuscxx/server-objects/IDBusServerObject.h"

using namespace testing;
using namespace sdbuscxxi;

class UTEST_SDBusCxxController : public Test
{
 public:
  UTEST_SDBusCxxController()
      : appCtx{std::make_shared<app::ApplicationContext>(argc, argv)},
        serverObject{std::make_shared<NiceMock<IDBusServerObject>>()}
  {
    ON_CALL(*serverObject, service_name())
        .WillByDefault(ReturnRef(serviceName));
    ON_CALL(*serverObject, object_path()).WillByDefault(ReturnRef(objectPath));

    // The controller builds a DBusServerObjectFactory internally; route every
    // created factory to hand out the fixture's mock server object.
    DBusServerObjectFactory::onMockCreate = [this](DBusServerObjectFactory& f) {
      EXPECT_CALL(f, create_default_object())
          .WillRepeatedly(Return(serverObject));
    };
    sdbus::mock::fail_bus_connection() = false;
    sdbus::mock::calls().clear();
  }

  ~UTEST_SDBusCxxController() override
  {
    DBusServerObjectFactory::onMockCreate = nullptr;
    sdbus::mock::fail_bus_connection() = false;
  }

  int argc{0};
  char** argv{nullptr};

  sdbus::ServiceName serviceName{"org.cppapptemplate.SimpleServer"};
  sdbus::ObjectPath objectPath{"/org/cppapptemplate/SimpleServer"};

  std::shared_ptr<app::ApplicationContext> appCtx;
  std::shared_ptr<NiceMock<IDBusServerObject>> serverObject;
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
  // inited() is false and run() bails out before entering serve().
  SDBusCxxController controller;

  EXPECT_FALSE(controller.run(appCtx));
}

TEST_F(UTEST_SDBusCxxController, run_succeeds_when_server_starts)
{
  // The raised stop flag ends the serving right away, so serve() exports the
  // object, claims the name, leaves the loop and reports success.
  SDBusCxxControllerPtr controller = SDBusCxxController::create();

  ASSERT_NE(controller, nullptr);

  appCtx->set_stop(true);

  EXPECT_TRUE(controller->run(appCtx));
  EXPECT_THAT(sdbus::mock::calls(),
              ElementsAre("requestName", "enterEventLoopAsync",
                          "leaveEventLoop", "releaseName"));
}

TEST_F(UTEST_SDBusCxxController, run_serves_until_the_stop_flag_is_raised)
{
  SDBusCxxControllerPtr controller = SDBusCxxController::create();

  ASSERT_NE(controller, nullptr);

  std::atomic_bool served{false};
  std::thread server{[&]() { served.store(controller->run(appCtx)); }};

  std::this_thread::sleep_for(std::chrono::milliseconds(300));

  EXPECT_FALSE(served.load());
  EXPECT_THAT(sdbus::mock::calls(), Not(Contains("leaveEventLoop")));

  appCtx->set_stop(true);
  server.join();

  EXPECT_TRUE(served.load());
  EXPECT_THAT(sdbus::mock::calls(), Contains("leaveEventLoop"));
}

TEST_F(UTEST_SDBusCxxController,
       run_returns_false_when_server_object_unavailable)
{
  DBusServerObjectFactory::onMockCreate = [](DBusServerObjectFactory& f) {
    EXPECT_CALL(f, create_default_object())
        .WillRepeatedly(Return(IDBusServerObjectPtr{}));
  };

  SDBusCxxControllerPtr controller = SDBusCxxController::create();

  ASSERT_NE(controller, nullptr);
  EXPECT_FALSE(controller->run(appCtx));
}

TEST_F(UTEST_SDBusCxxController, create_returns_null_when_bus_unavailable)
{
  sdbus::mock::fail_bus_connection() = true;

  EXPECT_EQ(SDBusCxxController::create(), nullptr);
}
