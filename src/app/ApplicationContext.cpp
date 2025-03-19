#include "src/app/ApplicationContext.h"

namespace app
{

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : argc{gargc}, argv{gargv}
{
  stop(false);
}

void ApplicationContext::stop(const bool nStop) { toStop.store(nStop); }

bool ApplicationContext::stop() { return toStop.load(); }

void ApplicationContext::push_error(const std::string& errorDescription)
{
  errors.emplace_back(errorDescription);
}

}  // namespace app
