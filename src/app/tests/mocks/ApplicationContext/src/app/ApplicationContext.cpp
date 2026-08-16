#include "src/app/ApplicationContext.h"

namespace app
{

const std::string ApplicationContext::default_db_name = "default_db_name";

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : margc{gargc}, margv{gargv}, mdb_dbname{default_db_name}
{
}

}  // namespace app
