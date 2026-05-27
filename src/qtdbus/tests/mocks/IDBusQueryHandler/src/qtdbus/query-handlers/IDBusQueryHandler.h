#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSQUERYHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSQUERYHANDLER_CLASS_H

#include <gmock/gmock.h>

#include <memory>

class QDBusConnection;

namespace qtdbusi
{

/**
 * @brief GMock mock of the IDBusQueryHandler interface, used by the
 * QtDBusController unit test to drive the query outcome without a bus.
 */
class IDBusQueryHandler
{
 public:
  using IDBusQueryHandlerPtr = std::shared_ptr<IDBusQueryHandler>;

  virtual ~IDBusQueryHandler() = default;
  IDBusQueryHandler() = default;

  MOCK_METHOD(bool, handle, (QDBusConnection * connection));
};

using IDBusQueryHandlerPtr = IDBusQueryHandler::IDBusQueryHandlerPtr;

}  // namespace qtdbusi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSQUERYHANDLER_CLASS_H
