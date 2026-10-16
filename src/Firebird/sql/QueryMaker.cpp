#include "src/Firebird/sql/QueryMaker.h"

#include <string>

namespace firebirdi::sql
{

std::string QueryMaker::make_date_query()
{
  return "SELECT CAST(CURRENT_DATE AS VARCHAR(20)) FROM RDB$DATABASE;";
}

}  // namespace firebirdi::sql
