#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_HOSTNAME1QUERYHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_HOSTNAME1QUERYHANDLER_CLASS_H

#include <QString>

#include "src/qtdbus/query-handlers/IDBusQueryHandler.h"

class QDBusConnection;

namespace qtdbusi
{

/**
 * @brief A query handler that reads a few well known, read only properties from
 * the systemd-hostnamed service (org.freedesktop.hostname1) on the system bus
 * through the native Qt D-Bus (Qt6::DBus) module.
 *
 * The bus (service) name, the object path and the interface name happen to
 * share the same reverse-DNS string for this particular freedesktop service,
 * but they are three independent D-Bus addressing coordinates and are therefore
 * kept as separate, explicitly named constants.
 */
class Hostname1QueryHandler : public IDBusQueryHandler
{
 public:
  /// @brief The hostname1 well known bus (service) name to route the call to.
  inline static const QString serviceName{"org.freedesktop.hostname1"};

  /// @brief The hostname1 object path the call is bound to.
  inline static const QString objectPath{"/org/freedesktop/hostname1"};

  /// @brief The interface that owns the queried properties. Distinct from the
  /// serviceName even though the string value coincides for this service.
  inline static const QString interfaceName{"org.freedesktop.hostname1"};

  /// @brief The static hostname property name.
  inline static const QString hostnameProperty{"Hostname"};
  /// @brief The pretty hostname property name.
  inline static const QString prettyHostnameProperty{"PrettyHostname"};
  /// @brief The operating system pretty name property name.
  inline static const QString osPrettyNameProperty{"OperatingSystemPrettyName"};
  /// @brief The OS kernel name property name.
  inline static const QString kernelNameProperty{"KernelName"};
  /// @brief The OS kernel release property name.
  inline static const QString kernelReleaseProperty{"KernelRelease"};
  /// @brief The chassis type property name.
  inline static const QString chassisProperty{"Chassis"};

  virtual ~Hostname1QueryHandler() = default;
  Hostname1QueryHandler() = default;

  /**
   * @brief Reads the hostname1 properties through the given connection and logs
   * them via the LOGI logging calls.
   *
   * @param connection A pointer to a valid, connected system bus connection.
   *
   * @return Returns true in case the properties were read successfully and
   * false in case of any D-Bus error or an invalid connection.
   */
  bool handle(QDBusConnection* connection) override;

 protected:
  /**
   * @brief The aggregated set of hostname1 properties read from the bus.
   */
  struct Hostname1Properties
  {
    QString hostname;
    QString prettyHostname;
    QString osPrettyName;
    QString kernelName;
    QString kernelRelease;
    QString chassis;
  };

  /**
   * @brief Reads the well known hostname1 properties from the bus in a single
   * org.freedesktop.DBus.Properties.GetAll round trip.
   *
   * This is the only method that actually talks to the bus and is intentionally
   * kept as a thin, overridable seam, so the handle() orchestration may be unit
   * tested without a live bus. The real implementation is exercised by the
   * component test against a live system bus.
   *
   * @param connection A pointer to a valid, connected system bus connection.
   * @param out The properties structure to fill on success.
   * @param error Set to a human readable description when false is returned.
   *
   * @return Returns true on success and false on any D-Bus error.
   */
  virtual bool fetch_properties(QDBusConnection* connection,
                                Hostname1Properties& out, QString& error);
};

}  // namespace qtdbusi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HOSTNAME1QUERYHANDLER_CLASS_H
