#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_TESTS_HOSTNAME1AVAILABILITY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_TESTS_HOSTNAME1AVAILABILITY_CLASS_H

#include <algorithm>
#include <string>
#include <vector>

#include "src/sdbuscxx/query-handlers/Hostname1QueryHandler.h"
#include "src/sdbuscxx/sdbuscxx-includes.h"

/**
 * @brief Tells the live test cases whether the bus they got carries the
 * hostname1 service at all: a container or a CI runner may expose a system
 * bus with no systemd-hostnamed behind it.
 */
class Hostname1Availability
{
 public:
  /**
   * @brief Asks the bus daemon whether the hostname1 name is owned or may be
   * activated.
   */
  static bool available(sdbus::IConnection& connection)
  {
    const std::string name{sdbuscxxi::Hostname1QueryHandler::serviceName};

    try {
      auto daemon = sdbus::createProxy(
          connection, sdbus::ServiceName{"org.freedesktop.DBus"},
          sdbus::ObjectPath{"/org/freedesktop/DBus"});

      bool owned{false};
      std::vector<std::string> activatable;

      daemon->callMethod("NameHasOwner")
          .onInterface("org.freedesktop.DBus")
          .withArguments(name)
          .storeResultsTo(owned);
      daemon->callMethod("ListActivatableNames")
          .onInterface("org.freedesktop.DBus")
          .storeResultsTo(activatable);

      return owned || std::find(activatable.cbegin(), activatable.cend(),
                                name) != activatable.cend();
    }
    catch (const sdbus::Error&) {
      return false;
    }
  }
};

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_TESTS_HOSTNAME1AVAILABILITY_CLASS_H
