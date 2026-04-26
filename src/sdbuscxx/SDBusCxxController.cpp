#include "SDBusCxxController.h"

#include <cassert>
#include <memory>
#include <exception>

#include <sdbus-c++/sdbus-c++.h>

#include "src/log/log.h"
#include "src/sdbuscxx/query-handlers/DBusQueryHandlerFactory.h"
#include "src/sdbuscxx/query-handlers/IDBusQueryHandler.h"

namespace sdbuscxxi
{

bool SDBusCxxController::run(std::shared_ptr<app::ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
      LOGE("No valid context pointer provided");
      return false;
  }

  appctx = ctx;

  if (!inited()) {
    LOGE("Object is not initialized");
    return false;
  }

  if (!make_example_demo_call()) {
      LOGE("Demo DBus call failure");
      return false;
  }

  return true;
}

bool SDBusCxxController::init()
{
  try {
    // Connect to the system bus (hostname1 and other well-known
    // system services are only exposed on the system bus)
    conn = sdbus::createSystemBusConnection();
  } catch (const std::exception& e) {
    LOGE("Exception during the connection object creation: " << e.what());
    return false;
  }

  assert(conn != nullptr);

  if (conn == nullptr) {
    LOGE("Fail to create a DBus connection");
    return false;
  }

  LOGD("DBus Connection created");

  return true;
}

bool SDBusCxxController::inited()
{
  return conn != nullptr;
}

bool SDBusCxxController::make_example_demo_call()
{
  assert(conn != nullptr);

  if (!inited()) {
    LOGE("Object is not initialized");
    return false;
  }

  DBusQueryHandlerFactory factory;

  IDBusQueryHandlerPtr handler = factory.create_default_handler();

  assert(handler != nullptr);

  if (handler == nullptr) {
    LOGE("Fail to create a DBus query handler");
    return false;
  }

  return handler->handle(conn.get());
}

SDBusCxxControllerPtr SDBusCxxController::create()
{
    SDBusCxxControllerPtr ptr = std::make_shared<SDBusCxxController>();

    if (!ptr->init()) {
      LOGE("Fail to init the newly created controller");
      return {};
    }

    return ptr;
}

}  // namespace sdbuscxxi
