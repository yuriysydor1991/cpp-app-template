#include "src/sqlite3cpp/sqlmaker/QueryMaker.h"

#include <cassert>
#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"

namespace sqlite3i::sqlmaker
{

QueryMaker::QueryMaker(std::shared_ptr<app::ApplicationContext> nctx)
    : actx{nctx}
{
  assert(actx != nullptr);
}

const std::string& QueryMaker::make_date_query()
{
  static const std::string date_query = "SELECT date('now');";

  return date_query;
}

}  // namespace sqlite3i::sqlmaker