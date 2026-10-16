#include "src/sqlite3cpp/SQLiteController.h"

#include <cassert>
#include <filesystem>
#include <memory>
#include <string>
#include <system_error>

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

  qmaker = create_query_maker();

  const std::filesystem::path dbpath{nctx->get_db_dbname()};
  std::error_code ec;

  if (dbpath.has_parent_path()) {
    std::filesystem::create_directories(dbpath.parent_path(), ec);
  }

  if (ec) {
    LOGE("Failure to create the database directory " << dbpath.parent_path()
                                                     << ": " << ec.message());
    return false;
  }

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

std::shared_ptr<sqlmaker::QueryMaker> SQLiteController::create_query_maker()
{
  return std::make_shared<sqlmaker::QueryMaker>();
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
