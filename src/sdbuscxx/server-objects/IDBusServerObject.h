#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSSERVEROBJECT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSSERVEROBJECT_CLASS_H

#include <memory>

#include <sdbus-c++/sdbus-c++.h>

/**
 * @brief The namespace to contain all the entities related to the sdbus-c++
 * based D-Bus server component.
 */
namespace sdbuscxxi
{

/**
 * @brief Interface for a server-side D-Bus object exported by the application.
 *
 * An implementation knows the well known bus (service) name to own and the
 * object path it lives at, and registers its interface vtable (properties,
 * methods, signals) onto a freshly created sdbus::IObject. The owning
 * SDBusCxxController is responsible for the connection life cycle, requesting
 * the name and running the event loop. This keeps the server plumbing and the
 * concrete exported object decoupled and independently testable.
 */
class IDBusServerObject
{
 public:
  using IDBusServerObjectPtr = std::shared_ptr<IDBusServerObject>;

  virtual ~IDBusServerObject() = default;
  IDBusServerObject() = default;

  /**
   * @brief The well known bus (service) name the server should own so that this
   * object becomes reachable by the clients.
   */
  virtual const sdbus::ServiceName& service_name() const = 0;

  /**
   * @brief The object path this object is exported at.
   */
  virtual const sdbus::ObjectPath& object_path() const = 0;

  /**
   * @brief Registers this object's interface vtable onto the given, freshly
   * created, sdbus object.
   *
   * @param object The sdbus object (created at object_path()) the vtable is
   * registered onto. The registration stays alive as long as the object does.
   */
  virtual void register_on(sdbus::IObject& object) = 0;
};

using IDBusServerObjectPtr = IDBusServerObject::IDBusServerObjectPtr;

}  // namespace sdbuscxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IDBUSSERVEROBJECT_CLASS_H
