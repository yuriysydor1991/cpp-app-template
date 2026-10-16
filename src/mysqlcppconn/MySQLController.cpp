#include "src/mysqlcppconn/MySQLController.h"

#include <cppconn/exception.h>
#include <cppconn/statement.h>

#include <cassert>
#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/log/log.h"
#include "src/mysqlcppconn/helpers/MySQLConnStrMaker.h"

namespace mysqli
{

MySQLController::MySQLController()
    : driver{*sql::mysql::get_mysql_driver_instance()}
{
}

bool MySQLController::connect(std::shared_ptr<app::ApplicationContext> nctx)
{
  assert(nctx);

  if (nctx == nullptr) {
    return false;
  }

  try {
    qmaker = std::make_unique<sqlmaker::QueryMaker>();

    auto connmaker = std::make_shared<helpers::MySQLConnStrMaker>();

    auto* cptr =
        driver.connect(connmaker->make_conn_string(nctx),
                       nctx->get_mysql_user(), nctx->get_mysql_password());

    assert(cptr != nullptr);

    if (cptr == nullptr) {
      return false;
    }

    conn = std::unique_ptr<sql::Connection>(cptr);

    if (!nctx->get_mysql_dbname().empty()) {
      conn->setSchema(nctx->get_mysql_dbname());
    }
  }
  catch (sql::SQLException& e) {
    LOGE("Failure to connect to the MySQL server: " << e.what());
  }

  return connected();
}

bool MySQLController::connected()
{
  return conn != nullptr && !conn->isClosed();
}

std::unique_ptr<sql::ResultSet> MySQLController::execute_query(
    const std::string& query)
{
  assert(conn != nullptr && !conn->isClosed());

  if (!connected()) {
    return {};
  }

  try {
    std::unique_ptr<sql::Statement> stmt(conn->createStatement());
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

    return res;
  }
  catch (sql::SQLException& e) {
    LOGE("Failure during the query execution: " << e.what()
                                                << "; query: " << query);
  }

  return {};
}

std::string MySQLController::get_current_date()
{
  assert(qmaker != nullptr);

  if (qmaker == nullptr) {
    return {};
  }

  try {
    auto res = execute_query(qmaker->make_date_query());

    if (res != nullptr && res->next()) {
      return res->getString(1).asStdString();
    }
  }
  catch (sql::SQLException& e) {
    LOGE("Failure to read the current date: " << e.what());
  }

  LOGE("No current date obtained");

  return {};
}

}  // namespace mysqli
