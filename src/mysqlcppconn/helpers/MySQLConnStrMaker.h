#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MYSQLCONNSTRMAKER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MYSQLCONNSTRMAKER_CLASS_H

#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"

/**
 * @brief the MySQL infrastructure helpers container namespace.
 */
namespace mysqli::helpers
{

/**
 * @brief A helper class for the conn string creation.
 */
class MySQLConnStrMaker
{
 public:
  virtual ~MySQLConnStrMaker() = default;
  MySQLConnStrMaker() = default;

  virtual std::string make_conn_string(
      std::shared_ptr<app::ApplicationContext> actx);
};

}  // namespace mysqli::helpers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MYSQLCONNSTRMAKER_CLASS_H
