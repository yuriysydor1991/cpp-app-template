#include "src/mysqlcppconn/MySQLController.h"

#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_connection.h>
#include <mysql_driver.h>

#include <cassert>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace mysqli
{

bool MySQLController::connect(std::shared_ptr<app::ApplicationContext> nctx)
{
  assert(nctx);

  if (nctx == nullptr) {
    return false;
  }

  return false;
}

bool MySQLController::connected() { return false; }

std::string MySQLController::get_current_date() { return {}; }

}  // namespace mysqli
