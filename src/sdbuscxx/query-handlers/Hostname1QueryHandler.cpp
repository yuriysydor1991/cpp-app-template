#include "src/sdbuscxx/query-handlers/Hostname1QueryHandler.h"

#include <cassert>
#include <memory>
#include <string>

#include <sdbus-c++/sdbus-c++.h>

#include "src/log/log.h"

namespace sdbuscxxi
{

bool Hostname1QueryHandler::handle(sdbus::IConnection* connection)
{
  assert(connection != nullptr);

  if (connection == nullptr) {
    LOGE("No valid bus connection provided");
    return false;
  }

  try {
    const Hostname1Properties props = fetch_properties(connection);

    LOGI("hostname: " << props.hostname);
    LOGI("Pretty hostname: " << props.prettyHostname);
    LOGI("OS name: " << props.osPrettyName);
  } catch (const sdbus::Error& e) {
    LOGE("DBus error: [" << e.getName() << "] " << e.getMessage());
    return false;
  }

  return true;
}

Hostname1QueryHandler::Hostname1Properties
Hostname1QueryHandler::fetch_properties(sdbus::IConnection* connection)
{
  assert(connection != nullptr);

  // The proxy memorizes the routing coordinates (the service/destination and
  // the object path). The interface that owns each property is supplied per
  // read through onInterface() - it is a separate addressing coordinate, not a
  // duplicate of the destination.
  std::unique_ptr<sdbus::IProxy> proxy =
      sdbus::createProxy(*connection, serviceName, objectPath);

  Hostname1Properties props;

  props.hostname = proxy->getProperty(hostnameProperty)
                       .onInterface(interfaceName)
                       .get<std::string>();

  props.prettyHostname = proxy->getProperty(prettyHostnameProperty)
                             .onInterface(interfaceName)
                             .get<std::string>();

  props.osPrettyName = proxy->getProperty(osPrettyNameProperty)
                           .onInterface(interfaceName)
                           .get<std::string>();

  return props;
}

}  // namespace sdbuscxxi
