#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CURRENTDATESERVEROBJECT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CURRENTDATESERVEROBJECT_CLASS_H

#include <ctime>
#include <string>

#include <sdbus-c++/sdbus-c++.h>

#include "src/sdbuscxx/server-objects/IDBusServerObject.h"

namespace sdbuscxxi
{

/**
 * @brief A simple server object that exposes a single read-only CurrentDate
 * property returning the current UTC date as a YYYY-MM-DD string.
 *
 * The bus (service) name, the object path and the interface name are kept as
 * three separate, explicitly typed constants - they are independent D-Bus
 * addressing coordinates even when their string values look alike.
 */
class CurrentDateServerObject : public IDBusServerObject
{
 public:
  /// @brief The well known bus (service) name the server owns.
  inline static const sdbus::ServiceName serviceName{
      "org.cppapptemplate.SimpleServer"};

  /// @brief The object path this object is exported at.
  inline static const sdbus::ObjectPath objectPath{
      "/org/cppapptemplate/SimpleServer"};

  /// @brief The (versioned) interface that owns the CurrentDate property.
  inline static const sdbus::InterfaceName interfaceName{
      "org.cppapptemplate.SimpleServer1"};

  /// @brief The current date property name.
  inline static const sdbus::PropertyName currentDateProperty{"CurrentDate"};

  virtual ~CurrentDateServerObject() = default;
  CurrentDateServerObject() = default;

  const sdbus::ServiceName& service_name() const override;
  const sdbus::ObjectPath& object_path() const override;
  void register_on(sdbus::IObject& object) override;

  /**
   * @brief Produces the value served by the CurrentDate property: the current
   * date as a YYYY-MM-DD (UTC) string.
   *
   * @return Returns the formatted current date string.
   */
  std::string current_date();

  /**
   * @brief Formats the given calendar time as a YYYY-MM-DD (UTC) string.
   *
   * Kept static and pure so it can be unit tested deterministically.
   *
   * @param timestamp The calendar time to format.
   *
   * @return Returns the formatted YYYY-MM-DD date string.
   */
  static std::string format_date(std::time_t timestamp);

 protected:
  /**
   * @brief Returns the current wall clock time. Overridable test seam so that
   * current_date() can be made deterministic in the unit tests.
   *
   * @return Returns the current calendar time.
   */
  virtual std::time_t now();
};

}  // namespace sdbuscxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CURRENTDATESERVEROBJECT_CLASS_H
