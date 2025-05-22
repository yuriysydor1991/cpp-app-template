#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_QUERYMAKER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_QUERYMAKER_CLASS_H

#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"

namespace mysqli::sqlmaker
{

/**
 * @brief The builder for the MySQL SQL queries.
 */
class QueryMaker
{
 public:
  virtual ~QueryMaker() = default;
  QueryMaker(std::shared_ptr<app::ApplicationContext> nctx);

  /**
   * @brief Returns the build date query for MySQL.
   */
  virtual const std::string& make_date_query();

 protected:
  std::shared_ptr<app::ApplicationContext> actx;
};

}  // namespace mysqli::sqlmaker

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_QUERYMAKER_CLASS_H