#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSSERVEROBJECT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSSERVEROBJECT_CLASS_H

#include <gmock/gmock.h>

#include <memory>

#include <sdbus-c++/sdbus-c++.h>

namespace sdbuscxxi
{

/**
 * @brief GMock mock of the IDBusServerObject interface, used by the
 * SDBusCxxController unit test to drive the serve() orchestration without a bus.
 */
class IDBusServerObject
{
 public:
  using IDBusServerObjectPtr = std::shared_ptr<IDBusServerObject>;

  virtual ~IDBusServerObject() = default;
  IDBusServerObject() = default;

  MOCK_METHOD(const sdbus::ServiceName&, service_name, (), (const));
  MOCK_METHOD(const sdbus::ObjectPath&, object_path, (), (const));
  MOCK_METHOD(void, register_on, (sdbus::IObject& object));
};

using IDBusServerObjectPtr = IDBusServerObject::IDBusServerObjectPtr;

}  // namespace sdbuscxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSSERVEROBJECT_CLASS_H
