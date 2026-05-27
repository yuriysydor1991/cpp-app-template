#include "src/qtdbus/QtDBusController.h"

#include <memory>

#include <QDBusConnection>
#include <QDBusError>

#include "src/log/log.h"
#include "src/qtdbus/query-handlers/DBusQueryHandlerFactory.h"
#include "src/qtdbus/query-handlers/IDBusQueryHandler.h"

namespace qtdbusi
{

bool QtDBusController::run()
{
  if (!inited()) {
    LOGE("Object is not initialized");
    return false;
  }

  return make_system_info_call();
}

bool QtDBusController::init()
{
  // Connect to the system bus - hostname1 and other well known system services
  // are only exposed there. QDBusConnection::systemBus() never throws; an
  // unreachable bus is reported through the connection state instead.
  connection.emplace(QDBusConnection::systemBus());

  if (!connection->isConnected()) {
    LOGE("Fail to connect to the system bus: "
         << connection->lastError().message().toStdString());
    return false;
  }

  LOGD("System D-Bus connection created");

  return true;
}

bool QtDBusController::inited() const
{
  return connection.has_value() && connection->isConnected();
}

QDBusConnection* QtDBusController::connection_ptr()
{
  return connection.has_value() ? &connection.value() : nullptr;
}

bool QtDBusController::make_system_info_call()
{
  DBusQueryHandlerFactory factory;

  IDBusQueryHandlerPtr handler = factory.create_default_handler();

  if (handler == nullptr) {
    LOGE("Fail to create a D-Bus query handler");
    return false;
  }

  return handler->handle(connection_ptr());
}

QtDBusControllerPtr QtDBusController::create()
{
  QtDBusControllerPtr ptr = std::make_shared<QtDBusController>();

  if (!ptr->init()) {
    LOGE("Fail to init the newly created controller");
    return {};
  }

  return ptr;
}

}  // namespace qtdbusi
