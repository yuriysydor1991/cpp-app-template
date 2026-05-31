#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSQUERYHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSQUERYHANDLER_CLASS_H

#include <gmock/gmock.h>

#include <memory>

namespace Gio
{
namespace DBus
{
class Connection;
}  // namespace DBus
}  // namespace Gio

namespace gdbusi
{

/**
 * @brief GMock mock of the IDBusQueryHandler interface, used by the
 * GDBusController unit test to drive the query outcome without a bus.
 */
class IDBusQueryHandler
{
 public:
  using IDBusQueryHandlerPtr = std::shared_ptr<IDBusQueryHandler>;

  virtual ~IDBusQueryHandler() = default;
  IDBusQueryHandler() = default;

  MOCK_METHOD(bool, handle, (Gio::DBus::Connection * connection));
};

using IDBusQueryHandlerPtr = IDBusQueryHandler::IDBusQueryHandlerPtr;

}  // namespace gdbusi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSQUERYHANDLER_CLASS_H
