#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_QUERYMAKER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_QUERYMAKER_CLASS_H

#include <string>

namespace pgsqli::sql
{

/**
 * @brief The builder for the PostgreSQL SQL queries.
 */
class QueryMaker
{
 public:
  virtual ~QueryMaker() = default;
  QueryMaker() = default;

  /**
   * @brief Returns the build date query for PostgreSQL.
   */
  virtual std::string make_date_query();
};

}  // namespace pgsqli::sql

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_QUERYMAKER_CLASS_H
