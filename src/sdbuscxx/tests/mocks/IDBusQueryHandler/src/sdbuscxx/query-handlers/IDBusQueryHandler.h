#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSQUERYHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSQUERYHANDLER_CLASS_H

#include <gmock/gmock.h>

#include <memory>

#include <sdbus-c++/sdbus-c++.h>

namespace sdbuscxxi
{

/**
 * @brief GMock mock of the IDBusQueryHandler interface, used by the
 * SDBusCxxController unit test to drive the demo call outcome without a bus.
 */
class IDBusQueryHandler
{
 public:
  using IDBusQueryHandlerPtr = std::shared_ptr<IDBusQueryHandler>;

  virtual ~IDBusQueryHandler() = default;
  IDBusQueryHandler() = default;

  MOCK_METHOD(bool, handle, (sdbus::IConnection* connection));
};

using IDBusQueryHandlerPtr = IDBusQueryHandler::IDBusQueryHandlerPtr;

}  // namespace sdbuscxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSQUERYHANDLER_CLASS_H
