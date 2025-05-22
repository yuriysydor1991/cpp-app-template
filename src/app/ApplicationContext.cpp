#include "src/app/ApplicationContext.h"

namespace app
{

const std::string ApplicationContext::default_mysql_name = "";
const std::string ApplicationContext::default_mysql_user = "template_test_user";
const std::string ApplicationContext::default_mysql_password =
    "template_test_password";

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : argc{gargc},
      argv{gargv},
      mysql_dbname{default_mysql_name},
      mysql_user{default_mysql_user},
      mysql_password{default_mysql_password}
{
}

void ApplicationContext::push_error(const std::string& errorDescription)
{
  errors.emplace_back(errorDescription);
}

}  // namespace app
