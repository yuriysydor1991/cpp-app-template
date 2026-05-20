#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FBCONNSTRINGMAKER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FBCONNSTRINGMAKER_CLASS_H

#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"

namespace firebirdi::helpers
{

/**
 * @brief The Firebird database connection string maker.
 *
 * Builds the Firebird database string in the `host/port:database` form (the
 * `host` and the `port` parts are omitted for a local connection). The user
 * name and the password are not part of the connection string in Firebird -
 * they are passed through the database parameter buffer by the driver instead.
 */
class FbConnStringMaker
{
 public:
  virtual ~FbConnStringMaker() = default;
  FbConnStringMaker() = default;

  virtual std::string make_conn_string(
      std::shared_ptr<app::ApplicationContext> actx);
};

}  // namespace firebirdi::helpers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FBCONNSTRINGMAKER_CLASS_H
