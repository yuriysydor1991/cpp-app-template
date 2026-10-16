#include "src/sqlite3cpp/sqlmaker/QueryMaker.h"

#include <string>

namespace sqlite3i::sqlmaker
{

const std::string& QueryMaker::make_date_query()
{
  static const std::string date_query = "SELECT date('now');";

  return date_query;
}

}  // namespace sqlite3i::sqlmaker
