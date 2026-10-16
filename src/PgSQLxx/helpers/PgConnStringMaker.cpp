#include "src/PgSQLxx/helpers/PgConnStringMaker.h"

#include <cassert>
#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"

namespace pgsqli::helpers
{

std::string PgConnStringMaker::make_conn_string(
    const std::shared_ptr<app::ApplicationContext>& actx)
{
  assert(actx != nullptr);

  if (actx == nullptr) {
    return {};
  }

  std::string connStr;

  // dbname='test' user='postgres' password='se cr\'et' host='localhost'

  append("dbname", actx->get_pg_dbname(), connStr);
  append("user", actx->get_pg_user(), connStr);
  append("password", actx->get_pg_password(), connStr);
  append("host", actx->get_pg_host(), connStr);
  append("port", actx->get_pg_port(), connStr);

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

  dst += field + "=" + quote(value);
}

std::string PgConnStringMaker::quote(const std::string& value)
{
  std::string quoted{"'"};

  for (const char c : value) {
    if (c == '\\' || c == '\'') {
      quoted += '\\';
    }

    quoted += c;
  }

  return quoted + "'";
}

}  // namespace pgsqli::helpers
