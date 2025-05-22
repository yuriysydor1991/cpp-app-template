#include "src/mysqlcppconn/sql/QueryMaker.h"

#include <cassert>
#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"

namespace mysqli::sqlmaker
{

QueryMaker::QueryMaker(std::shared_ptr<app::ApplicationContext> nctx)
    : actx{nctx}
{
  assert(actx != nullptr);
}

const std::string& QueryMaker::make_date_query()
{
  static const std::string date_query = "SELECT CURDATE();";

  return date_query;
}

}  // namespace mysqli::sqlmaker
