#include "src/gdbus/query-handlers/Hostname1QueryHandler.h"

#include <cassert>
#include <map>

#include <giomm/dbusconnection.h>
#include <glibmm/error.h>
#include <glibmm/ustring.h>
#include <glibmm/variant.h>

#include "src/log/log.h"

namespace gdbusi
{

namespace
{

/// @brief The org.freedesktop.DBus.Properties.GetAll reply maps each property
/// name to its value boxed in a D-Bus variant (a{sv}). giomm unboxes that
/// variant level on extraction, so the map values are the plain typed variants.
using PropertiesMap = std::map<Glib::ustring, Glib::VariantBase>;

/**
 * @brief Extracts a string property from an org.freedesktop.DBus.Properties
 * GetAll (a{sv}) result. Returns an empty string when the property is absent or
 * not a string, so a single odd property never aborts the whole read.
 */
std::string property_string(const PropertiesMap& properties,
                            const Glib::ustring& name)
{
  const auto it = properties.find(name);

  if (it == properties.end()) {
    return {};
  }

  try {
    return Glib::VariantBase::cast_dynamic<Glib::Variant<Glib::ustring>>(
               it->second)
        .get();
  }
  catch (const std::bad_cast&) {
    return {};
  }
}

}  // namespace

bool Hostname1QueryHandler::handle(Gio::DBus::Connection* connection)
{
  assert(connection != nullptr);

  if (connection == nullptr) {
    LOGE("No valid bus connection provided");
    return false;
  }

  Hostname1Properties props;
  std::string error;

  if (!fetch_properties(connection, props, error)) {
    LOGE("D-Bus error while reading hostname1 properties: " << error);
    return false;
  }

  LOGI("hostname: " << props.hostname);
  LOGI("Pretty hostname: " << props.prettyHostname);
  LOGI("OS name: " << props.osPrettyName);
  LOGI("Kernel: " << props.kernelName << " " << props.kernelRelease);
  LOGI("Chassis: " << props.chassis);

  return true;
}

bool Hostname1QueryHandler::fetch_properties(Gio::DBus::Connection* connection,
                                             Hostname1Properties& out,
                                             std::string& error)
{
  assert(connection != nullptr);

  try {
    // A single org.freedesktop.DBus.Properties.GetAll call returns every
    // property exposed by the hostname1 interface in one a{sv} round trip. The
    // interface whose properties are wanted is supplied as the call argument -
    // it is a separate addressing coordinate, not a duplicate of the
    // destination.
    const auto parameters = Glib::VariantContainerBase::create_tuple(
        Glib::Variant<Glib::ustring>::create(interfaceName));

    const Glib::VariantContainerBase reply = connection->call_sync(
        objectPath, propertiesInterfaceName, "GetAll", parameters, serviceName);

    // The reply is a tuple wrapping a single a{sv} dictionary.
    Glib::Variant<PropertiesMap> dictVariant;
    reply.get_child(dictVariant, 0);

    const PropertiesMap properties = dictVariant.get();

    out.hostname = property_string(properties, hostnameProperty);
    out.prettyHostname = property_string(properties, prettyHostnameProperty);
    out.osPrettyName = property_string(properties, osPrettyNameProperty);
    out.kernelName = property_string(properties, kernelNameProperty);
    out.kernelRelease = property_string(properties, kernelReleaseProperty);
    out.chassis = property_string(properties, chassisProperty);
  }
  catch (const Glib::Error& ex) {
    error = ex.what();
    return false;
  }

  return true;
}

}  // namespace gdbusi
