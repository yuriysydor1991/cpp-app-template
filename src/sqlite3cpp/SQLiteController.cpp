#include "src/sqlite3cpp/SQLiteController.h"

#include <SQLiteCpp/SQLiteCpp.h>

#include <cassert>
#include <iostream>
#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/app/IDBConnection.h"

namespace sqlite3i
{

bool SQLiteController::connect(std::shared_ptr<app::ApplicationContext> nctx)
{
  assert(nctx != nullptr);

  if (nctx == nullptr) {
    return false;
  }

  actx = nctx;

  qmaker = std::make_shared<sqlmaker::QueryMaker>(actx);

  try {
    db = std::make_shared<SQLite::Database>(
        nctx->db_dbname, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  }
  catch (const std::exception& e) {
    std::cerr << "SQLite exception: " << e.what() << '\n';
    return false;
  }

  return db != nullptr;
}

bool SQLiteController::connected()
{
  return db != nullptr && db->getHandle() != nullptr;
}

std::string SQLiteController::get_current_date()
{
  assert(db != nullptr);
  assert(qmaker != nullptr);

  auto qdate = execute_select_query(qmaker->make_date_query());

  assert(qdate != nullptr);

  if (qdate == nullptr) {
    return {};
  }

  return qdate->getColumn(0);
}

std::shared_ptr<SQLite::Statement> SQLiteController::execute_select_query(
    const std::string& query)
{
  assert(db != nullptr);
  assert(!query.empty());

  if (!connected() || query.empty()) {
    return {};
  }

  std::shared_ptr<SQLite::Statement> squery;

  try {
    squery = std::make_shared<SQLite::Statement>(*db, query);

    squery->executeStep();
  }
  catch (const std::exception& e) {
    std::cerr << "SQLite exception: " << e.what() << std::endl;
    return squery;
  }

  return squery;
}

}  // namespace sqlite3i
