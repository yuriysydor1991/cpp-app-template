#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_TESTABLEHOSTNAME1QUERYHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_TESTABLEHOSTNAME1QUERYHANDLER_CLASS_H

#include <QString>
#include <functional>

#include "src/qtdbus/query-handlers/Hostname1Properties.h"
#include "src/qtdbus/query-handlers/Hostname1QueryHandler.h"

class QDBusConnection;

namespace qtdbusi
{

/**
 * @brief Test double that replaces the only bus-touching method with a
 * configurable callback, so the handle() orchestration (and its LOGI logging)
 * can be exercised in isolation, without a live D-Bus.
 */
class TestableHostname1QueryHandler : public Hostname1QueryHandler
{
 public:
  std::function<bool(QDBusConnection*, Hostname1Properties&, QString&)> onFetch;

 protected:
  bool fetch_properties(QDBusConnection* connection, Hostname1Properties& out,
                        QString& error) override
  {
    if (onFetch) {
      return onFetch(connection, out, error);
    }

    return false;
  }
};

}  // namespace qtdbusi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_TESTABLEHOSTNAME1QUERYHANDLER_CLASS_H
