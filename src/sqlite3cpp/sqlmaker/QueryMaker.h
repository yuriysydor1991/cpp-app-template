#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SQLITE_QUERYMAKER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SQLITE_QUERYMAKER_CLASS_H

#include <string>

namespace sqlite3i::sqlmaker
{

/**
 * @brief The class designed to encapsulate the SQL query string buildup.
 */
class QueryMaker
{
 public:
  virtual ~QueryMaker() = default;
  QueryMaker() = default;

  /// @brief Returns the SQL query that selects the current date.
  virtual const std::string& make_date_query();
};

}  // namespace sqlite3i::sqlmaker

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SQLITE_QUERYMAKER_CLASS_H
