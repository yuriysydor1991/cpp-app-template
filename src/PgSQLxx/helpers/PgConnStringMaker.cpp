#include "src/PgSQLxx/helpers/PgConnStringMaker.h"

#include <cassert>
#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"

namespace pgsqli::helpers
{

std::string PgConnStringMaker::make_conn_string(
    std::shared_ptr<app::ApplicationContext> actx)
{
  assert(actx != nullptr);

  if (actx == nullptr) {
    return {};
  }

  std::string connStr;

  // "dbname=test user=postgres password=secret host=localhost port=5432"

  append("dbname", actx->pg_dbname, connStr);
  append("user", actx->pg_user, connStr);
  append("password", actx->pg_password, connStr);
  append("host", actx->pg_host, connStr);
  append("port", actx->pg_port, connStr);

  return connStr;
}

void PgConnStringMaker::append(const std::string& field,
                               const std::string& value, std::string& dst)
{
  assert(!field.empty());

  if (field.empty() || value.empty()) {
    return;
  }

  if (!dst.empty()) {
    dst += " ";
  }

  dst += field + "=" + value;
}

}  // namespace pgsqli::helpers
