#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_QUERYMAKER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_QUERYMAKER_CLASS_H

#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"

namespace pgsqli::sql
{

/**
 * @brief The builder for the PostgreSQL SQL queries.
 */
class QueryMaker
{
 public:
  virtual ~QueryMaker() = default;
  explicit QueryMaker(std::shared_ptr<app::ApplicationContext> nctx);

  /**
   * @brief Returns the build date query for PostgreSQL.
   */
  virtual std::string make_date_query();

 protected:
  std::shared_ptr<app::ApplicationContext> actx;
};

}  // namespace pgsqli::sql

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_QUERYMAKER_CLASS_H
