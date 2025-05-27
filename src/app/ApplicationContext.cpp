#include "src/app/ApplicationContext.h"

#include <memory>
#include <string>

#include "project-global-decls.h"

namespace app
{

const std::string ApplicationContext::default_db_name =
    project_decls::PROJECT_NAME + project_decls::PROJECT_BUILD_VERSION +
    std::string{".db"};

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : argc{gargc}, argv{gargv}, db_dbname{default_db_name}
{
}

void ApplicationContext::push_error(const std::string& errorDescription)
{
  errors.emplace_back(errorDescription);
}

}  // namespace app
