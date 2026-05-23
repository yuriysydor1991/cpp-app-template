#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_DBUSQUERYHANDLERFACTORY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_DBUSQUERYHANDLERFACTORY_CLASS_H

#include <gmock/gmock.h>

#include <functional>

#include "src/sdbuscxx/query-handlers/IDBusQueryHandler.h"

namespace sdbuscxxi
{

/**
 * @brief GMock mock of the DBusQueryHandlerFactory. The controller constructs
 * the factory internally, so an onMockCreate seam (the same idiom as the app
 * component mocks) lets a test configure each created instance.
 */
class DBusQueryHandlerFactory
{
 public:
  virtual ~DBusQueryHandlerFactory() = default;

  DBusQueryHandlerFactory()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  MOCK_METHOD(IDBusQueryHandlerPtr, create_hostname1_handler, ());
  MOCK_METHOD(IDBusQueryHandlerPtr, create_default_handler, ());

  inline static std::function<void(DBusQueryHandlerFactory&)> onMockCreate;
};

}  // namespace sdbuscxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DBUSQUERYHANDLERFACTORY_CLASS_H
