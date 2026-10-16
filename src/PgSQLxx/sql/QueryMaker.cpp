#include "src/PgSQLxx/sql/QueryMaker.h"

#include <string>

namespace pgsqli::sql
{

std::string QueryMaker::make_date_query() { return "SELECT CURRENT_DATE;"; }

}  // namespace pgsqli::sql
