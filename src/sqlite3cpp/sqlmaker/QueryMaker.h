#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SQLITE_QUERYMAKER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SQLITE_QUERYMAKER_CLASS_H

#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"

namespace sqlite3i::sqlmaker
{

/**
 * @brief The class designed to encapsulate the SQL query string buildup.
 */
class QueryMaker
{
 public:
  virtual ~QueryMaker() = default;
  explicit QueryMaker(std::shared_ptr<app::ApplicationContext> nctx);

  virtual const std::string& make_date_query();

 protected:
  std::shared_ptr<app::ApplicationContext> actx;
};

}  // namespace sqlite3i::sqlmaker

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SQLITE_QUERYMAKER_CLASS_H
