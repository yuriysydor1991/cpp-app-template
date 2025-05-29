#include "src/app/ApplicationContext.h"

namespace app
{

const std::string ApplicationContext::default_db_name = "default_db_name";

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : argc{gargc}, argv{gargv}, db_dbname{default_db_name}
{
}

}  // namespace app