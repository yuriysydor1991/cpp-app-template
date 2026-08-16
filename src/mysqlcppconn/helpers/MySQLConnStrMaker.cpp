#include "src/mysqlcppconn/helpers/MySQLConnStrMaker.h"

#include <cassert>
#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"

namespace mysqli::helpers
{

std::string MySQLConnStrMaker::make_conn_string(
    std::shared_ptr<app::ApplicationContext> actx)
{
  assert(actx != nullptr);

  if (actx == nullptr) {
    return {};
  }

  std::string cstr = actx->get_mysql_host();

  if (!actx->get_mysql_port().empty()) {
    cstr += ":" + actx->get_mysql_port();
  }

  return cstr;
}

}  // namespace mysqli::helpers
