#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_HOSTNAME1PROPERTIES_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_HOSTNAME1PROPERTIES_CLASS_H

#include <string>

namespace sdbuscxxi
{

/**
 * @brief The aggregated set of the hostname1 properties read from the bus.
 */
struct Hostname1Properties
{
  std::string hostname;
  std::string prettyHostname;
  std::string osPrettyName;
};

}  // namespace sdbuscxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HOSTNAME1PROPERTIES_CLASS_H
