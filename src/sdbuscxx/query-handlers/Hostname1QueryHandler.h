#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_HOSTNAME1QUERYHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_HOSTNAME1QUERYHANDLER_CLASS_H

#include <memory>
#include <string>

#include <sdbus-c++/sdbus-c++.h>

#include "src/sdbuscxx/query-handlers/IDBusQueryHandler.h"

namespace sdbuscxxi
{

/**
 * @brief A query handler that reads a few well known, read only properties from
 * the systemd-hostnamed service (org.freedesktop.hostname1) on the system bus.
 *
 * The bus (service) name, the object path and the interface name happen to
 * share the same reverse-DNS string for this particular freedesktop service,
 * but they are three independent DBus addressing coordinates and are therefore
 * kept as separate, explicitly typed constants.
 */
class Hostname1QueryHandler : public IDBusQueryHandler
{
 public:
  /// @brief The hostname1 well known bus (service) name to route the call to.
  inline static const sdbus::ServiceName serviceName{
      "org.freedesktop.hostname1"};

  /// @brief The hostname1 object path the proxy is bound to.
  inline static const sdbus::ObjectPath objectPath{
      "/org/freedesktop/hostname1"};

  /// @brief The interface that owns the queried properties. Distinct from the
  /// serviceName even though the string value coincides for this service.
  inline static const sdbus::InterfaceName interfaceName{
      "org.freedesktop.hostname1"};

  /// @brief The static hostname property name.
  inline static const sdbus::PropertyName hostnameProperty{"Hostname"};

  /// @brief The pretty hostname property name.
  inline static const sdbus::PropertyName prettyHostnameProperty{
      "PrettyHostname"};

  /// @brief The operating system pretty name property name.
  inline static const sdbus::PropertyName osPrettyNameProperty{
      "OperatingSystemPrettyName"};

  virtual ~Hostname1QueryHandler() = default;
  Hostname1QueryHandler() = default;

  /**
   * @brief Reads the hostname1 properties through the given connection and logs
   * them.
   *
   * @param connection A pointer to a valid, connected system bus connection.
   *
   * @return Returns true in case all the properties were read successfully and
   * false in case of any DBus error or an invalid connection.
   */
  bool handle(sdbus::IConnection* connection) override;

 protected:
  /**
   * @brief The aggregated set of hostname1 properties read from the bus.
   */
  struct Hostname1Properties
  {
    std::string hostname;
    std::string prettyHostname;
    std::string osPrettyName;
  };

  /**
   * @brief Creates a proxy bound to the hostname1 service and reads the three
   * well known properties from it.
   *
   * This is the only method that actually talks to the bus and is intentionally
   * kept as a thin, overridable seam, so the handle() orchestration may be unit
   * tested without a live bus. The real implementation is exercised by the
   * component test against a live system bus.
   *
   * @param connection A pointer to a valid, connected system bus connection.
   *
   * @return Returns the filled properties structure.
   *
   * @throws sdbus::Error in case the proxy creation or any property read fails.
   */
  virtual Hostname1Properties fetch_properties(sdbus::IConnection* connection);
};

}  // namespace sdbuscxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HOSTNAME1QUERYHANDLER_CLASS_H
