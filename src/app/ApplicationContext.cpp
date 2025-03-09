#include "src/app/ApplicationContext.h"

namespace app
{

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : argc{gargc}, argv{gargv}
{
}

void ApplicationContext::push_error(const std::string& errorDescription)
{
  errors.emplace_back(errorDescription);
}

}  // namespace app
