#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_DBUSSERVEROBJECTFACTORY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_DBUSSERVEROBJECTFACTORY_CLASS_H

#include <gmock/gmock.h>

#include <functional>

#include "src/sdbuscxx/server-objects/IDBusServerObject.h"

namespace sdbuscxxi
{

/**
 * @brief GMock mock of the DBusServerObjectFactory. The controller constructs
 * the factory internally, so an onMockCreate seam (the same idiom as the app
 * component mocks) lets a test configure each created instance.
 */
class DBusServerObjectFactory
{
 public:
  virtual ~DBusServerObjectFactory() = default;

  DBusServerObjectFactory()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  MOCK_METHOD(IDBusServerObjectPtr, create_current_date_object, ());
  MOCK_METHOD(IDBusServerObjectPtr, create_default_object, ());

  inline static std::function<void(DBusServerObjectFactory&)> onMockCreate;
};

}  // namespace sdbuscxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DBUSSERVEROBJECTFACTORY_CLASS_H
