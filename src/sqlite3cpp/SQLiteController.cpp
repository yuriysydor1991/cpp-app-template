#include "src/sqlite3cpp/SQLiteController.h"

#include <cassert>
#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"
#include "src/app/IDBConnection.h"
#include "src/log/log.h"
#include "src/sqlite3cpp/sqlitecpp-includes.h"

namespace sqlite3i
{

bool SQLiteController::connect(std::shared_ptr<app::ApplicationContext> nctx)
{
  assert(nctx != nullptr);

  if (nctx == nullptr) {
    LOGE("No valid application context pointer provided");
    return false;
  }

  qmaker = std::make_shared<sqlmaker::QueryMaker>();

  try {
    db = std::make_shared<SQLite::Database>(
        nctx->get_db_dbname(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  }
  catch (const std::exception& e) {
    LOGE("SQLite exception: " << e.what());
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
  if (!connected() || qmaker == nullptr) {
    LOGE("No connection available");
    return {};
  }

  return select_scalar(qmaker->make_date_query());
}

std::string SQLiteController::select_scalar(const std::string& query)
{
  assert(db != nullptr);
  assert(!query.empty());

  try {
    SQLite::Statement squery{*db, query};

    if (squery.executeStep()) {
      return squery.getColumn(0).getString();
    }

    LOGE("No rows returned for the query: " << query);
  }
  catch (const std::exception& e) {
    LOGE("SQLite exception: " << e.what() << "; query: " << query);
  }

  return {};
}

}  // namespace sqlite3i
