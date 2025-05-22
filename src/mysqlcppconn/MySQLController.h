#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MYSQLCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MYSQLCONTROLLER_CLASS_H

#include <mysql_connection.h>
#include <mysql_driver.h>

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/app/IDBConnection.h"

/**
 * @brief Interface for the MySQL connection abstraction layer for the
 * application.
 */
namespace mysqli
{

/**
 * @brief The implemented interface for the MySQL DBMS connection.
 * Declare and implement new methods to introduce new queries.
 */
class MySQLController : public app::IDBConnection
{
 public:
  virtual ~MySQLController() = default;
  MySQLController();

  /**
   * @brief Tries to connect to the specified database server.
   * The credentials are taken from the ApplicationContext instance.
   *
   * @param nctx The ApplicationContext for connection credentials etc.
   *
   * @returns Returns a true boolean value on the success or false otherwise.
   */
  virtual bool connect(std::shared_ptr<app::ApplicationContext> nctx) override;

  /**
   * @brief Returns a true boolean value in case of a present
   * connection.
   *
   * @returns Returns a true boolean value in case of a present
   * connection or false otherwise.
   */
  virtual bool connected() override;

  /**
   * @brief The demonstration method which fetches current date as a string from
   * the available server connection if any.
   *
   * @returns Returns retrieved date from the database if any, or empty string
   * in case of any error.
   */
  virtual std::string get_current_date() override;

 protected:
  sql::mysql::MySQL_Driver& driver;

  std::unique_ptr<sql::Connection> conn;
};

}  // namespace mysqli

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MYSQLCONTROLLER_CLASS_H
