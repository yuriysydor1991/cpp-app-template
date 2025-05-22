#include "src/app/ApplicationContext.h"

namespace app
{

const std::string ApplicationContext::default_mysql_name = "";
const std::string ApplicationContext::default_mysql_user = "template_test_user";
const std::string ApplicationContext::default_mysql_password =
    "template_test_password";
const std::string ApplicationContext::default_mysql_host = "tcp://127.0.0.1";
const std::string ApplicationContext::default_mysql_port = "3306";

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : argc{gargc},
      argv{gargv},
      mysql_dbname{default_mysql_name},
      mysql_user{default_mysql_user},
      mysql_password{default_mysql_password},
      mysql_host{default_mysql_host},
      mysql_port{default_mysql_port}
{
}

void ApplicationContext::push_error(const std::string& errorDescription)
{
  errors.emplace_back(errorDescription);
}

}  // namespace app
