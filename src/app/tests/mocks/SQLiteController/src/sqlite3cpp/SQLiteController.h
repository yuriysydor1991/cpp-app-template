#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SQLITECONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SQLITECONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"
#include "src/app/IDBConnection.h"

namespace sqlite3i
{

class SQLiteController : public app::IDBConnection
{
 public:
  virtual ~SQLiteController() = default;
  SQLiteController()
  {
    if (onMockCreate != nullptr) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(SQLiteController&)> onMockCreate;

  MOCK_METHOD(bool, connect, (std::shared_ptr<app::ApplicationContext> nctx));

  MOCK_METHOD(bool, connected, ());

  MOCK_METHOD(std::string, get_current_date, ());
};

}  // namespace sqlite3i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SQLITECONTROLLER_CLASS_H
