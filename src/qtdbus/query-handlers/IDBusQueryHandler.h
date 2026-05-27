#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSQUERYHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSQUERYHANDLER_CLASS_H

#include <memory>

class QDBusConnection;

/**
 * @brief The namespace to contain all the entities related to the Qt D-Bus
 * (QtDBus, Qt6::DBus) based system bus client component.
 */
namespace qtdbusi
{

class SystemInformation;

/**
 * @brief Interface for the system D-Bus query handlers.
 *
 * A query handler encapsulates a single, self contained interaction with some
 * well known D-Bus service (reading a set of properties, calling a method,
 * etc.) and stores the obtained data into the passed SystemInformation holder.
 * The owning QtDBusController is responsible for establishing the bus
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
   * bus connection and fill the provided system information holder.
   *
   * @param connection A pointer to a valid, connected bus connection owned by
   * the caller. Must not be a nullptr.
   * @param info The system information holder to populate with the obtained
   * data (and, on failure, with a human readable error description).
   *
   * @return Returns true in case of success and false in case of any error.
   */
  virtual bool handle(QDBusConnection* connection, SystemInformation& info) = 0;
};

using IDBusQueryHandlerPtr = IDBusQueryHandler::IDBusQueryHandlerPtr;

}  // namespace qtdbusi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSQUERYHANDLER_CLASS_H
