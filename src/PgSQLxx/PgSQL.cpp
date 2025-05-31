#include "src/PgSQLxx/PgSQL.h"

#include <cassert>
#include <memory>

#include "src/PgSQLxx/helpers/PgConnStringMaker.h"
#include "src/app/IApplication.h"
#include "src/log/log.h"

namespace pgsqli
{

bool PgSQL::connect(std::shared_ptr<app::ApplicationContext> nctx)
{
  assert(nctx != nullptr);

  if (nctx == nullptr) {
    LOGE("No valid application context provided")
    return false;
  }

  actx = nctx;

  qmaker = create_query_maker();
  pgsqlc = create_connection();

  return pgsqlc != nullptr && pgsqlc->is_open();
}

std::shared_ptr<pqxx::connection> PgSQL::create_connection()
{
  try {
    return std::make_shared<pqxx::connection>(make_conn_string());
  }
  catch (const std::exception& e) {
    LOGE("failure while creating the db connection: " << e.what());
  }

  return {};
}

std::shared_ptr<sql::QueryMaker> PgSQL::create_query_maker()
{
  return std::make_shared<sql::QueryMaker>(actx);
}

std::string PgSQL::make_conn_string()
{
  auto csmaker = std::make_shared<helpers::PgConnStringMaker>();

  return csmaker->make_conn_string(actx);
}

bool PgSQL::connected()
{
  assert(pgsqlc != nullptr);

  return pgsqlc != nullptr && pgsqlc->is_open();
}

std::string PgSQL::get_current_date()
{
  assert(pgsqlc != nullptr);
  assert(qmaker != nullptr);

  if (!connected()) {
    LOGE("Not connected");
    return {};
  }

  static const std::string dquery = qmaker->make_date_query();

  auto pgres = execute_query(dquery);

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
