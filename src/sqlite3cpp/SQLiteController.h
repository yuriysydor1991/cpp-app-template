#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SQLITECONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SQLITECONTROLLER_CLASS_H

#include <SQLiteCpp/SQLiteCpp.h>

#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"
#include "src/app/IDBConnection.h"
#include "src/sqlite3cpp/sqlmaker/QueryMaker.h"

namespace sqlite3i
{

/**
 * @brief The SQLiteCpp db manager. Encapsulates and executes the SQL queries
 * with the nice method interface.
 */
class SQLiteController : public app::IDBConnection
{
 public:
  virtual ~SQLiteController() = default;
  SQLiteController() = default;

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

 private:
  std::shared_ptr<SQLite::Statement> execute_select_query(
      const std::string& query);

  std::shared_ptr<app::ApplicationContext> actx;
  std::shared_ptr<SQLite::Database> db;
  std::shared_ptr<sqlmaker::QueryMaker> qmaker;
};

}  // namespace sqlite3i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SQLITECONTROLLER_CLASS_H
