#include "src/app/ApplicationContext.h"

namespace app
{

const std::string ApplicationContext::default_pg_name = "postgres";
const std::string ApplicationContext::default_pg_user = "template_test_user";
const std::string ApplicationContext::default_pg_password =
    "template_test_password";

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : argc{gargc},
      argv{gargv},
      pg_dbname{default_pg_name},
      pg_user{default_pg_user},
      pg_password{default_pg_password}
{
}

void ApplicationContext::push_error(const std::string& errorDescription)
{
  errors.emplace_back(errorDescription);
}

}  // namespace app
