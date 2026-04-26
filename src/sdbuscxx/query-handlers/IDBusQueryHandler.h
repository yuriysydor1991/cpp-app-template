#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSQUERYHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSQUERYHANDLER_CLASS_H

#include <memory>

#include <sdbus-c++/sdbus-c++.h>

/**
 * @brief The namespace to contain all the entities related to the sdbus-c++
 * based system DBus client component.
 */
namespace sdbuscxxi
{

/**
 * @brief Interface for the system DBus query handlers.
 *
 * A query handler encapsulates a single, self contained interaction with some
 * well known DBus service (reading a set of properties, calling a method,
 * etc.). The owning SDBusCxxController is responsible for establishing the bus
 * connection and passing it down to the handler. This keeps the connection life
 * cycle and the concrete query logic decoupled and independently testable.
 */
class IDBusQueryHandler
{
 public:
  using IDBusQueryHandlerPtr = std::shared_ptr<IDBusQueryHandler>;

  virtual ~IDBusQueryHandler() = default;
  IDBusQueryHandler() = default;

  /**
   * @brief Execute the handler's query against the given, already established,
   * bus connection.
   *
   * @param connection A pointer to a valid, connected bus connection owned by
   * the caller. Must not be a nullptr.
   *
   * @return Returns true in case of success and false in case of any error.
   */
  virtual bool handle(sdbus::IConnection* connection) = 0;
};

using IDBusQueryHandlerPtr = IDBusQueryHandler::IDBusQueryHandlerPtr;

}  // namespace sdbuscxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSQUERYHANDLER_CLASS_H
