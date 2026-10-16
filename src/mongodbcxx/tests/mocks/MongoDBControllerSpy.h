#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MONGODBCONTROLLERSPY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MONGODBCONTROLLERSPY_CLASS_H

#include <gmock/gmock.h>

#include <memory>

#include "src/mongodbcxx/MongoDBController.h"

namespace mongodbcxxi
{

/**
 * @brief The real MongoDBController with the query execution replaced by a
 * mock method, so the controller logic runs with no MongoDB server.
 */
class MongoDBControllerSpy : public MongoDBController
{
 public:
  ~MongoDBControllerSpy() override = default;
  MongoDBControllerSpy() = default;

  MOCK_METHOD(std::shared_ptr<DBJsonRes>, execute_query, (JsonDoc queryDoc),
              (override));
};

}  // namespace mongodbcxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MONGODBCONTROLLERSPY_CLASS_H
