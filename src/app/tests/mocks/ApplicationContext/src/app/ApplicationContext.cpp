#include "ApplicationContext.h"

namespace app
{

const std::string ApplicationContext::default_mysql_name = "default_mysql_name";
const std::string ApplicationContext::default_mysql_user = "default_mysql_user";
const std::string ApplicationContext::default_mysql_password =
    "default_mysql_password";
const std::string ApplicationContext::default_mysql_host = "default_mysql_host";
const std::string ApplicationContext::default_mysql_port = "default_mysql_port";

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : margc{gargc},
      margv{gargv},
      mmysql_dbname{default_mysql_name},
      mmysql_user{default_mysql_user},
      mmysql_password{default_mysql_password},
      mmysql_host{default_mysql_host},
      mmysql_port{default_mysql_port}
{
  // The pushed errors are kept like the real context keeps them, so the test
  // cases see them through the get_errors accessor too.
  ON_CALL(*this, push_error(testing::_))
      .WillByDefault([this](const std::string& errorDescription) {
        merrors.push_back(errorDescription);
      });
}

}  // namespace app
