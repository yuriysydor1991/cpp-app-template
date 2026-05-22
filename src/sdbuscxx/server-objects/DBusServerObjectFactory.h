#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_DBUSSERVEROBJECTFACTORY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_DBUSSERVEROBJECTFACTORY_CLASS_H

#include "src/sdbuscxx/server-objects/IDBusServerObject.h"

namespace sdbuscxxi
{

/**
 * @brief A factory that creates the server-side D-Bus object instances exported
 * by the application.
 *
 * For now the factory exposes a single object (the current date one) and
 * returns it as the default object. New exported objects are meant to be added
 * here as the project grows.
 */
class DBusServerObjectFactory
{
 public:
  virtual ~DBusServerObjectFactory() = default;
  DBusServerObjectFactory() = default;

  /**
   * @brief Creates the current date server object.
   *
   * @return Returns the created object instance.
   */
  virtual IDBusServerObjectPtr create_current_date_object();

  /**
   * @brief Creates the default server object.
   *
   * For now this is the current date server object.
   *
   * @return Returns the created default object instance.
   */
  virtual IDBusServerObjectPtr create_default_object();
};

}  // namespace sdbuscxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DBUSSERVEROBJECTFACTORY_CLASS_H
