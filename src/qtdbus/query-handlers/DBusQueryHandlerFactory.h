#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_DBUSQUERYHANDLERFACTORY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_DBUSQUERYHANDLERFACTORY_CLASS_H

#include "src/qtdbus/query-handlers/IDBusQueryHandler.h"

namespace qtdbusi
{

/**
 * @brief A factory that creates the system D-Bus query handler instances.
 *
 * For now the factory exposes a single concrete handler (the hostname1 one) and
 * returns it as the default handler. New well known service handlers are meant
 * to be added here as the project grows.
 */
class DBusQueryHandlerFactory
{
 public:
  virtual ~DBusQueryHandlerFactory() = default;
  DBusQueryHandlerFactory() = default;

  /**
   * @brief Creates the hostname1 (systemd-hostnamed) query handler.
   *
   * @return Returns the created handler instance.
   */
  virtual IDBusQueryHandlerPtr create_hostname1_handler();

  /**
   * @brief Creates the default query handler.
   *
   * For now this is the hostname1 query handler.
   *
   * @return Returns the created default handler instance.
   */
  virtual IDBusQueryHandlerPtr create_default_handler();
};

}  // namespace qtdbusi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DBUSQUERYHANDLERFACTORY_CLASS_H
