#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSQUERYHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSQUERYHANDLER_CLASS_H

#include <memory>

namespace Gio
{
namespace DBus
{
class Connection;
}  // namespace DBus
}  // namespace Gio

/**
 * @brief The namespace to contain all the entities related to the GLib GDBus
 * (gtkmm4/giomm Gio::DBus) based system bus client component.
 */
namespace gdbusi
{

/**
 * @brief Interface for the system D-Bus query handlers.
 *
 * A query handler encapsulates a single, self contained interaction with some
 * well known D-Bus service (reading a set of properties, calling a method,
 * etc.) and logs the obtained data. The owning GDBusController is responsible
 * for establishing the bus connection and passing it down to the handler. This
 * keeps the connection life cycle and the concrete query logic decoupled and
 * independently testable.
 */
class IDBusQueryHandler
{
 public:
  using IDBusQueryHandlerPtr = std::shared_ptr<IDBusQueryHandler>;

  virtual ~IDBusQueryHandler() = default;
  IDBusQueryHandler() = default;

  /**
   * @brief Execute the handler's query against the given, already established,
   * bus connection and log the obtained data.
   *
   * @param connection A pointer to a valid, connected bus connection owned by
   * the caller. Must not be a nullptr.
   *
   * @return Returns true in case of success and false in case of any error.
   */
  virtual bool handle(Gio::DBus::Connection* connection) = 0;
};

using IDBusQueryHandlerPtr = IDBusQueryHandler::IDBusQueryHandlerPtr;

}  // namespace gdbusi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSQUERYHANDLER_CLASS_H
