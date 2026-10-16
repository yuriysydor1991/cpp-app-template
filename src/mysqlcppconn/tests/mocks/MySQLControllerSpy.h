#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MYSQLCONTROLLERSPY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MYSQLCONTROLLERSPY_CLASS_H

#include <gmock/gmock.h>

#include <memory>
#include <string>

#include "src/mysqlcppconn/MySQLController.h"

namespace mysqli
{

/**
 * @brief The MySQLController with the server talking seams mocked, so the
 * controller logic runs without a MySQL server.
 */
class MySQLControllerSpy : public MySQLController
{
 public:
  MOCK_METHOD(std::unique_ptr<sql::Connection>, open_connection,
              (const std::string& url, const std::string& user,
               const std::string& password),
              (override));

  MOCK_METHOD(std::unique_ptr<sql::ResultSet>, execute_query,
              (const std::string& query), (override));
};

}  // namespace mysqli

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MYSQLCONTROLLERSPY_CLASS_H
