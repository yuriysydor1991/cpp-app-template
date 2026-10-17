#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_HOSTNAME1PROPERTIES_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_HOSTNAME1PROPERTIES_CLASS_H

#include <QString>

namespace qtdbusi
{

/**
 * @brief The aggregated set of the hostname1 properties read from the bus.
 */
class Hostname1Properties
{
 public:
  QString hostname;
  QString prettyHostname;
  QString osPrettyName;
  QString kernelName;
  QString kernelRelease;
  QString chassis;
};

}  // namespace qtdbusi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HOSTNAME1PROPERTIES_CLASS_H
