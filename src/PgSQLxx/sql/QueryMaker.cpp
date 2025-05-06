#include "src/PgSQLxx/sql/QueryMaker.h"

#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"

namespace pgsqli::sql
{

QueryMaker::QueryMaker(std::shared_ptr<app::ApplicationContext> nctx)
    : actx{nctx}
{
}

std::string QueryMaker::make_date_query() { return "SELECT CURRENT_DATE;"; }

}  // namespace pgsqli::sql
