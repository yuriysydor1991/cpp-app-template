#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PGCONNSTRINGMAKER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PGCONNSTRINGMAKER_CLASS_H

#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"

namespace pgsqli::helpers
{

/**
 * @brief The PostgreSQL connection string maker.
 */
class PgConnStringMaker
{
 public:
  virtual ~PgConnStringMaker() = default;
  PgConnStringMaker() = default;

  virtual std::string make_conn_string(
      std::shared_ptr<app::ApplicationContext> actx);

 private:
  static void append(const std::string& field, const std::string& value,
                     std::string& dst);
};

}  // namespace pgsqli::helpers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PGCONNSTRINGMAKER_CLASS_H
