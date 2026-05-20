#include "src/Firebird/sql/QueryMaker.h"

#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"

namespace firebirdi::sql
{

QueryMaker::QueryMaker(std::shared_ptr<app::ApplicationContext> nctx)
    : actx{nctx}
{
}

std::string QueryMaker::make_date_query()
{
  return "SELECT CAST(CURRENT_DATE AS VARCHAR(20)) FROM RDB$DATABASE;";
}

}  // namespace firebirdi::sql
