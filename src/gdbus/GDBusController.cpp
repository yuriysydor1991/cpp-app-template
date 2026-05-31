#include "src/gdbus/GDBusController.h"

#include <memory>

#include <giomm/dbusconnection.h>
#include <glibmm/error.h>

#include "src/gdbus/query-handlers/DBusQueryHandlerFactory.h"
#include "src/gdbus/query-handlers/IDBusQueryHandler.h"
#include "src/log/log.h"

namespace gdbusi
{

bool GDBusController::run()
{
  if (!inited()) {
    LOGE("Object is not initialized");
    return false;
  }

  return make_system_info_call();
}

bool GDBusController::init()
{
  // Connect to the system bus - hostname1 and other well known system services
  // are only exposed there. get_sync() throws a Glib::Error when the bus is not
  // reachable in the current environment.
  try {
    connection = Gio::DBus::Connection::get_sync(Gio::DBus::BusType::SYSTEM);
  }
  catch (const Glib::Error& ex) {
    LOGE("Fail to connect to the system bus: " << ex.what());
    return false;
  }

  if (!connection) {
    LOGE("The system bus connection is empty");
    return false;
  }

  LOGD("System D-Bus connection created");

  return true;
}

bool GDBusController::inited() const { return static_cast<bool>(connection); }

Gio::DBus::Connection* GDBusController::connection_ptr()
{
  return connection ? connection.get() : nullptr;
}

bool GDBusController::make_system_info_call()
{
  DBusQueryHandlerFactory factory;

  IDBusQueryHandlerPtr handler = factory.create_default_handler();

  if (handler == nullptr) {
    LOGE("Fail to create a D-Bus query handler");
    return false;
  }

  return handler->handle(connection_ptr());
}

GDBusControllerPtr GDBusController::create()
{
  GDBusControllerPtr ptr = std::make_shared<GDBusController>();

  if (!ptr->init()) {
    LOGE("Fail to init the newly created controller");
    return {};
  }

  return ptr;
}

}  // namespace gdbusi
