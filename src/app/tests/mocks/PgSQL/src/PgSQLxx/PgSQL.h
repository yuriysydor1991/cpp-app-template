#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PGSQL_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PGSQL_CLASS_H

#include <memory>
#include <functional>

#include <gmock/gmock.h>

#include "src/PgSQLxx/sql/QueryMaker.h"
#include "src/app/ApplicationContext.h"
#include "src/app/IDBConnection.h"

namespace pgsqli
{

class PgSQL : public app::IDBConnection
{
 public:
  virtual ~PgSQL() = default;
  PgSQL()
  {
    if (onMockCreate) { onMockCreate(*this) ; }
  }

  inline static std::function<void(PgSQL&)> onMockCreate;

  MOCK_METHOD(bool, connect, (std::shared_ptr<app::ApplicationContext> nctx), (override));
  MOCK_METHOD(bool, connected, (), (override));
  MOCK_METHOD(std::string, get_current_date, (), (override));
};

}  // namespace pgsqli

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PGSQL_CLASS_H
