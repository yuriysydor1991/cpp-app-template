#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_HOSTNAME1PROPERTIES_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_HOSTNAME1PROPERTIES_CLASS_H

#include <string>

namespace gdbusi
{

/**
 * @brief The aggregated set of the hostname1 properties read from the bus.
 */
class Hostname1Properties
{
 public:
  std::string hostname;
  std::string prettyHostname;
  std::string osPrettyName;
  std::string kernelName;
  std::string kernelRelease;
  std::string chassis;
};

}  // namespace gdbusi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HOSTNAME1PROPERTIES_CLASS_H
