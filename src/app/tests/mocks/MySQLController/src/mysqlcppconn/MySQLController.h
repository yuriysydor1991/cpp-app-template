#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MYSQLCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MYSQLCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/app/IDBConnection.h"
#include "src/mysqlcppconn/sql/QueryMaker.h"

namespace mysqli
{

class MySQLController : public app::IDBConnection
{
 public:
  virtual ~MySQLController() = default;
  MySQLController()
  {
    if (onMockCreate != nullptr) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(MySQLController&)> onMockCreate;

  MOCK_METHOD(bool, connect, (std::shared_ptr<app::ApplicationContext> nctx));

  MOCK_METHOD(bool, connected, ());

  MOCK_METHOD(std::string, get_current_date, ());
};

}  // namespace mysqli

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MYSQLCONTROLLER_CLASS_H
