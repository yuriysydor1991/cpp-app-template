#include "src/mysqlcppconn/MySQLController.h"

#include <cppconn/exception.h>
#include <cppconn/statement.h>

#include <cassert>
#include <memory>

#include "src/app/ApplicationContext.h"
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
    auto connmaker = std::make_shared<helpers::MySQLConnStrMaker>();

    auto* cptr = driver.connect(connmaker->make_conn_string(nctx),
                                nctx->mysql_user, nctx->mysql_password);

    assert(cptr != nullptr);

    if (cptr == nullptr) {
      return false;
    }

    conn = std::unique_ptr<sql::Connection>(cptr);

    if (!nctx->mysql_dbname.empty()) {
      conn->setSchema(nctx->mysql_dbname);
    }
  }
  catch (sql::SQLException& e) {
    std::cerr << "Error: " << e.what() << std::endl;
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
  assert(connected());

  if (!connected()) {
    return {};
  }

  try {
    std::unique_ptr<sql::Statement> stmt(conn->createStatement());
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

    return res;
  }
  catch (sql::SQLException& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return {};
}

std::string MySQLController::get_current_date()
{
  auto res = execute_query("SELECT CURDATE();");

  return res->getString(1);
}

}  // namespace mysqli
