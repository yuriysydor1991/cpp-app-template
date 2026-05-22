#include "SDBusCxxController.h"

#include <cassert>
#include <exception>
#include <memory>

#include <sdbus-c++/sdbus-c++.h>

#include "src/log/log.h"
#include "src/sdbuscxx/server-objects/DBusServerObjectFactory.h"
#include "src/sdbuscxx/server-objects/IDBusServerObject.h"

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

  if (!serve()) {
    LOGE("DBus server failure");
    return false;
  }

  return true;
}

bool SDBusCxxController::init()
{
  try {
    // Connect to the session bus: this simple server owns its own well known
    // name, and requesting a name on the session bus needs no extra policy
    // (unlike the system bus, which requires a /etc/dbus-1/system.d rule).
    conn = sdbus::createSessionBusConnection();
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

bool SDBusCxxController::serve()
{
  assert(conn != nullptr);

  if (!inited()) {
    LOGE("Object is not initialized");
    return false;
  }

  DBusServerObjectFactory factory;

  serverObject = factory.create_default_object();

  assert(serverObject != nullptr);

  if (serverObject == nullptr) {
    LOGE("Fail to create a DBus server object");
    return false;
  }

  try {
    // Create the object at its path, register its interface vtable, then claim
    // the well known name and start serving requests.
    object = sdbus::createObject(*conn, serverObject->object_path());

    serverObject->register_on(*object);

    conn->requestName(serverObject->service_name());

    LOGI("DBus server is running on the session bus. Service: "
         << serverObject->service_name()
         << ", object: " << serverObject->object_path());

    conn->enterEventLoop();
  } catch (const sdbus::Error& e) {
    LOGE("DBus error: [" << e.getName() << "] " << e.getMessage());
    return false;
  }

  return true;
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
