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

  /**
   * @brief Builds the libpq key=value connection string out of the context
   * credentials. Every value is single-quoted with the backslashes and quotes
   * escaped, so values with spaces or quotes stay intact and can't inject
   * other connection keywords.
   */
  virtual std::string make_conn_string(
      const std::shared_ptr<app::ApplicationContext>& actx);

 private:
  static void append(const std::string& field, const std::string& value,
                     std::string& dst);

  static std::string quote(const std::string& value);
};

}  // namespace pgsqli::helpers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PGCONNSTRINGMAKER_CLASS_H
