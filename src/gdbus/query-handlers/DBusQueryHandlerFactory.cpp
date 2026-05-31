#include "src/gdbus/query-handlers/DBusQueryHandlerFactory.h"

#include <memory>

#include "src/gdbus/query-handlers/Hostname1QueryHandler.h"
#include "src/gdbus/query-handlers/IDBusQueryHandler.h"
#include "src/log/log.h"

namespace gdbusi
{

IDBusQueryHandlerPtr DBusQueryHandlerFactory::create_hostname1_handler()
{
  return std::make_shared<Hostname1QueryHandler>();
}

IDBusQueryHandlerPtr DBusQueryHandlerFactory::create_default_handler()
{
  LOGT("Creating the default (hostname1) D-Bus query handler");

  return create_hostname1_handler();
}

}  // namespace gdbusi
