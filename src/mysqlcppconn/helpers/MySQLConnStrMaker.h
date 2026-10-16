#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MYSQLCONNSTRMAKER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MYSQLCONNSTRMAKER_CLASS_H

#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"

/**
 * @brief the MySQL infrastructure helpers container namespace.
 */
namespace mysqli::helpers
{

/**
 * @brief A helper class for the conn string creation.
 */
class MySQLConnStrMaker
{
 public:
  virtual ~MySQLConnStrMaker() = default;
  MySQLConnStrMaker() = default;

  /**
   * @brief Makes the Connector/C++ host URL, e.g. the tcp://127.0.0.1:3306,
   * out of the context's MySQL host and port. A host given as an URL already,
   * e.g. the unix:///run/mysqld/mysqld.sock, keeps its scheme.
   *
   * @param actx The ApplicationContext with the MySQL host and port.
   *
   * @returns Returns the host URL or an empty string for no context.
   */
  virtual std::string make_conn_string(
      std::shared_ptr<app::ApplicationContext> actx);
};

}  // namespace mysqli::helpers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MYSQLCONNSTRMAKER_CLASS_H
