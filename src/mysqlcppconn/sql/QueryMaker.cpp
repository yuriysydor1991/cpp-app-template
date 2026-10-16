#include "src/mysqlcppconn/sql/QueryMaker.h"

#include <string>

namespace mysqli::sqlmaker
{

const std::string& QueryMaker::make_date_query()
{
  static const std::string date_query = "SELECT CURDATE();";

  return date_query;
}

}  // namespace mysqli::sqlmaker
