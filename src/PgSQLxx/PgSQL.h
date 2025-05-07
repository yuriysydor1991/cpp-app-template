#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PGSQL_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PGSQL_CLASS_H

#include <memory>
#include <pqxx/pqxx>

#include "src/PgSQLxx/sql/QueryMaker.h"
#include "src/app/ApplicationContext.h"
#include "src/app/IDBConnection.h"

/**
 * @brief The namespace to encapsulate all the guts of the PostgreSQL
 * database handling.
 */
namespace pgsqli
{

/**
 * @brief The interface to the PostgreSQL connection.
 */
class PgSQL : public app::IDBConnection
{
 public:
  virtual ~PgSQL() = default;
  PgSQL() = default;

  /**
   * @brief Tries to connect to the specified PostgreSQL database server.
   * The credentials are taken from the ApplicationContext instance.
   *
   * @param nctx The ApplicationContext for connection credentials etc.
   *
   * @returns Returns a true boolean value on the success or false otherwise.
   */
  virtual bool connect(std::shared_ptr<app::ApplicationContext> nctx) override;

  /**
   * @brief Returns a true boolean value in case of a present PostgreSQL
   * connection.
   *
   * @returns Returns a true boolean value in case of a present PostgreSQL
   * connection or false otherwise.
   */
  virtual bool connected() override;

  /**
   * @brief The demonstration method which fetches current date as a string from
   * the available PostgreSQL server connection if any.
   *
   * @returns Returns retrieved date from the database if any, or empty string
   * in case of any error.
   */
  virtual std::string get_current_date() override;

 protected:
  virtual std::string make_conn_string();

  virtual pqxx::result execute_query(const std::string& query);

  virtual std::shared_ptr<pqxx::connection> create_connection();
  virtual std::shared_ptr<sql::QueryMaker> create_query_maker();

 private:
  std::shared_ptr<app::ApplicationContext> actx;

  std::shared_ptr<pqxx::connection> pgsqlc;
  std::shared_ptr<sql::QueryMaker> qmaker;
};

}  // namespace pgsqli

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PGSQL_CLASS_H
