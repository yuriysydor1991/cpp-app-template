#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FIREBIRD_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FIREBIRD_CLASS_H

#include <memory>
#include <string>

#include "src/Firebird/IFbClient.h"
#include "src/Firebird/sql/QueryMaker.h"
#include "src/app/ApplicationContext.h"
#include "src/app/IDBConnection.h"

namespace firebirdi
{

/**
 * @brief The interface to the Firebird database connection.
 *
 * The class orchestrates the connection string building, the credentials and
 * the SQL query making while delegating every native Firebird call to an
 * injected IFbClient implementation.
 */
class Firebird : public app::IDBConnection
{
 public:
  virtual ~Firebird() = default;
  Firebird() = default;

  /**
   * @brief Tries to connect to the specified Firebird database server.
   * The credentials are taken from the ApplicationContext instance.
   *
   * @param nctx The ApplicationContext for connection credentials etc.
   *
   * @returns Returns a true boolean value on the success or false otherwise.
   */
  virtual bool connect(std::shared_ptr<app::ApplicationContext> nctx) override;

  /**
   * @brief Returns a true boolean value in case of a present Firebird
   * connection.
   *
   * @returns Returns a true boolean value in case of a present Firebird
   * connection or false otherwise.
   */
  virtual bool connected() override;

  /**
   * @brief The demonstration method which fetches current date as a string from
   * the available Firebird server connection if any.
   *
   * @returns Returns retrieved date from the database if any, or empty string
   * in case of any error.
   */
  virtual std::string get_current_date() override;

 protected:
  virtual std::string make_conn_string();

  /**
   * @brief Creates the IFbClient implementation used to talk to Firebird.
   *
   * Overridden by the tests to inject a fake/mock client so the orchestration
   * may be exercised without the native library or a running server.
   */
  virtual std::shared_ptr<IFbClient> create_client();
  virtual std::shared_ptr<sql::QueryMaker> create_query_maker();

 private:
  std::shared_ptr<app::ApplicationContext> actx;

  std::shared_ptr<IFbClient> client;
  std::shared_ptr<sql::QueryMaker> qmaker;
};

}  // namespace firebirdi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FIREBIRD_CLASS_H
