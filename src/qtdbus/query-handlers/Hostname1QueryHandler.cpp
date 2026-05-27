#include "src/qtdbus/query-handlers/Hostname1QueryHandler.h"

#include <cassert>

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDBusVariant>
#include <QMap>
#include <QVariant>

#include "src/log/log.h"

namespace qtdbusi
{

namespace
{

/**
 * @brief Extracts a string property from an org.freedesktop.DBus.Properties
 * GetAll (a{sv}) result, transparently unwrapping the D-Bus variant level if
 * QtDBus did not flatten it already.
 */
QString property_string(const QVariantMap& properties, const QString& name)
{
  const QVariant value = properties.value(name);

  if (value.canConvert<QDBusVariant>()) {
    return value.value<QDBusVariant>().variant().toString();
  }

  return value.toString();
}

}  // namespace

bool Hostname1QueryHandler::handle(QDBusConnection* connection)
{
  assert(connection != nullptr);

  if (connection == nullptr) {
    LOGE("No valid bus connection provided");
    return false;
  }

  Hostname1Properties props;
  QString error;

  if (!fetch_properties(connection, props, error)) {
    LOGE("D-Bus error while reading hostname1 properties: "
         << error.toStdString());
    return false;
  }

  LOGI("hostname: " << props.hostname.toStdString());
  LOGI("Pretty hostname: " << props.prettyHostname.toStdString());
  LOGI("OS name: " << props.osPrettyName.toStdString());
  LOGI("Kernel: " << props.kernelName.toStdString() << " "
                  << props.kernelRelease.toStdString());
  LOGI("Chassis: " << props.chassis.toStdString());

  return true;
}

bool Hostname1QueryHandler::fetch_properties(QDBusConnection* connection,
                                             Hostname1Properties& out,
                                             QString& error)
{
  assert(connection != nullptr);

  // A single org.freedesktop.DBus.Properties.GetAll call returns every property
  // exposed by the hostname1 interface in one a{sv} round trip. The interface
  // whose properties are wanted is supplied as the call argument - it is a
  // separate addressing coordinate, not a duplicate of the destination.
  QDBusInterface properties(serviceName, objectPath,
                            QStringLiteral("org.freedesktop.DBus.Properties"),
                            *connection);

  if (!properties.isValid()) {
    error = properties.lastError().message();
    if (error.isEmpty()) {
      error =
          QStringLiteral("the %1 service is not available").arg(serviceName);
    }
    return false;
  }

  const QDBusReply<QVariantMap> reply =
      properties.call(QStringLiteral("GetAll"), interfaceName);

  if (!reply.isValid()) {
    error = reply.error().message();
    return false;
  }

  const QVariantMap map = reply.value();

  out.hostname = property_string(map, hostnameProperty);
  out.prettyHostname = property_string(map, prettyHostnameProperty);
  out.osPrettyName = property_string(map, osPrettyNameProperty);
  out.kernelName = property_string(map, kernelNameProperty);
  out.kernelRelease = property_string(map, kernelReleaseProperty);
  out.chassis = property_string(map, chassisProperty);

  return true;
}

}  // namespace qtdbusi
