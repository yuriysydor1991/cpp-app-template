#include "src/PgSQLxx/PgSQL.h"

#include <cassert>
#include <memory>

#include "src/PgSQLxx/helpers/PgConnStringMaker.h"
#include "src/app/applications/IApplication.h"
#include "src/log/log.h"

namespace pgsqli
{

bool PgSQL::connect(std::shared_ptr<app::ApplicationContext> nctx)
{
  assert(nctx != nullptr);

  if (nctx == nullptr) {
    LOGE("No valid application context provided");
    return false;
  }

  qmaker = create_query_maker();
  pgsqlc = create_connection(make_conn_string(nctx));

  return connected();
}

std::shared_ptr<pqxx::connection> PgSQL::create_connection(
    const std::string& connStr)
{
  try {
    return std::make_shared<pqxx::connection>(connStr);
  }
  catch (const std::exception& e) {
    LOGE("failure while creating the db connection: " << e.what());
  }

  return {};
}

std::shared_ptr<sql::QueryMaker> PgSQL::create_query_maker()
{
  return std::make_shared<sql::QueryMaker>();
}

std::string PgSQL::make_conn_string(
    const std::shared_ptr<app::ApplicationContext>& nctx)
{
  auto csmaker = std::make_shared<helpers::PgConnStringMaker>();

  return csmaker->make_conn_string(nctx);
}

bool PgSQL::connected() { return pgsqlc != nullptr && pgsqlc->is_open(); }

std::string PgSQL::get_current_date()
{
  if (!connected()) {
    LOGE("Not connected");
    return {};
  }

  assert(qmaker != nullptr);

  auto pgres = execute_query(qmaker->make_date_query());

  if (pgres.empty()) {
    LOGE("Empty result obtained");
    return {};
  }

  auto rows = pgres.front();

  return rows[0].as<std::string>();
}

pqxx::result PgSQL::execute_query(const std::string& query)
{
  assert(pgsqlc != nullptr);
  assert(!query.empty());

  try {
    pqxx::work tx(*pgsqlc);

    pqxx::result r = tx.exec(query);

    tx.commit();

    return r;
  }
  catch (std::exception const& e) {
    LOGE("Failure during the query execution: " << e.what()
                                                << "; query: " << query);
  }

  return {};
}

}  // namespace pgsqli
