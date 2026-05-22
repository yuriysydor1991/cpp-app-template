#include "src/sdbuscxx/server-objects/DBusServerObjectFactory.h"

#include <memory>

#include "src/log/log.h"
#include "src/sdbuscxx/server-objects/CurrentDateServerObject.h"
#include "src/sdbuscxx/server-objects/IDBusServerObject.h"

namespace sdbuscxxi
{

IDBusServerObjectPtr DBusServerObjectFactory::create_current_date_object()
{
  return std::make_shared<CurrentDateServerObject>();
}

IDBusServerObjectPtr DBusServerObjectFactory::create_default_object()
{
  LOGT("Creating the default (current date) DBus server object");

  return create_current_date_object();
}

}  // namespace sdbuscxxi
