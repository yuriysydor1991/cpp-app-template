#include "src/app/ApplicationContext.h"

namespace app
{

const std::string ApplicationContext::default_fb_name = "employee";
const std::string ApplicationContext::default_fb_user = "SYSDBA";
const std::string ApplicationContext::default_fb_password = "masterkey";

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : argc{gargc},
      argv{gargv},
      fb_dbname{default_fb_name},
      fb_user{default_fb_user},
      fb_password{default_fb_password}
{
}

void ApplicationContext::push_error(const std::string& errorDescription)
{
  errors.emplace_back(errorDescription);
}

}  // namespace app
