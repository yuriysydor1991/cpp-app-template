#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PGSQLSPY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PGSQLSPY_CLASS_H

#include <memory>
#include <string>

#include "src/PgSQLxx/PgSQL.h"

namespace pgsqli
{

/**
 * @brief The PgSQL test double that needs no server: it records the
 * connection string the PgSQL builds and creates no connection.
 */
class PgSQLSpy : public PgSQL
{
 public:
  std::string connStr;
  int connectionsCreated{0};

 protected:
  std::shared_ptr<pqxx::connection> create_connection(
      const std::string& nconnStr) override
  {
    connStr = nconnStr;
    ++connectionsCreated;
    return {};
  }
};

}  // namespace pgsqli

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PGSQLSPY_CLASS_H
