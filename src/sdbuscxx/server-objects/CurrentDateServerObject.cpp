#include "src/sdbuscxx/server-objects/CurrentDateServerObject.h"

#include <ctime>
#include <string>

#include <sdbus-c++/sdbus-c++.h>

namespace sdbuscxxi
{

const sdbus::ServiceName& CurrentDateServerObject::service_name() const
{
  return serviceName;
}

const sdbus::ObjectPath& CurrentDateServerObject::object_path() const
{
  return objectPath;
}

void CurrentDateServerObject::register_on(sdbus::IObject& object)
{
  // The CurrentDate property is read-only: a getter and no setter. The vtable
  // registration is owned by the sdbus object and stays alive together with it.
  object
      .addVTable(sdbus::registerProperty(currentDateProperty)
                     .withGetter([this]() { return current_date(); }))
      .forInterface(interfaceName);
}

std::string CurrentDateServerObject::current_date()
{
  return format_date(now());
}

std::string CurrentDateServerObject::format_date(std::time_t timestamp)
{
  std::tm tmv{};
  ::gmtime_r(&timestamp, &tmv);

  char buffer[16] = {0};
  std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tmv);

  return std::string{buffer};
}

std::time_t CurrentDateServerObject::now()
{
  return std::time(nullptr);
}

}  // namespace sdbuscxxi
