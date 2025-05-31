#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MONGODBCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MONGODBCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/app/IDBConnection.h"

namespace mongodbcxxi
{

class MongoDBController : public app::IDBConnection
{
 public:
  virtual ~MongoDBController() = default;
  MongoDBController()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(MongoDBController&)> onMockCreate;

  MOCK_METHOD(bool, connect, (std::shared_ptr<app::ApplicationContext> nctx),
              (override));

  MOCK_METHOD(bool, connected, (), (override));

  MOCK_METHOD(std::string, get_current_date, (), (override));
};

}  // namespace mongodbcxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MONGODBCONTROLLER_CLASS_H
