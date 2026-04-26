#include "src/sdbuscxx/query-handlers/DBusQueryHandlerFactory.h"

#include <memory>

#include "src/log/log.h"
#include "src/sdbuscxx/query-handlers/Hostname1QueryHandler.h"
#include "src/sdbuscxx/query-handlers/IDBusQueryHandler.h"

namespace sdbuscxxi
{

IDBusQueryHandlerPtr DBusQueryHandlerFactory::create_hostname1_handler()
{
  return std::make_shared<Hostname1QueryHandler>();
}

IDBusQueryHandlerPtr DBusQueryHandlerFactory::create_default_handler()
{
  LOGT("Creating the default (hostname1) DBus query handler");

  return create_hostname1_handler();
}

}  // namespace sdbuscxxi
