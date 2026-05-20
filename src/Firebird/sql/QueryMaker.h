#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FIREBIRD_QUERYMAKER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FIREBIRD_QUERYMAKER_CLASS_H

#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"

namespace firebirdi::sql
{

/**
 * @brief The builder for the Firebird SQL queries.
 */
class QueryMaker
{
 public:
  virtual ~QueryMaker() = default;
  explicit QueryMaker(std::shared_ptr<app::ApplicationContext> nctx);

  /**
   * @brief Returns the build date query for Firebird.
   *
   * Firebird requires a FROM clause even for scalar selects, hence the
   * RDB$DATABASE system table is used. The value is cast to a VARCHAR so the
   * driver may fetch it as a plain string.
   */
  virtual std::string make_date_query();

 protected:
  std::shared_ptr<app::ApplicationContext> actx;
};

}  // namespace firebirdi::sql

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FIREBIRD_QUERYMAKER_CLASS_H
