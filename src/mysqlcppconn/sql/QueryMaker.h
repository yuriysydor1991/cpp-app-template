#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_QUERYMAKER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_QUERYMAKER_CLASS_H

#include <string>

namespace mysqli::sqlmaker
{

/**
 * @brief The builder for the MySQL SQL queries.
 */
class QueryMaker
{
 public:
  virtual ~QueryMaker() = default;
  QueryMaker() = default;

  /**
   * @brief Returns the build date query for MySQL.
   */
  virtual const std::string& make_date_query();
};

}  // namespace mysqli::sqlmaker

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_QUERYMAKER_CLASS_H
