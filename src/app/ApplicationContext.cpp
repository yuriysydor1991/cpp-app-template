#include "src/app/ApplicationContext.h"

namespace app
{

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : argc{gargc},
      argv{gargv},
      http_address{default_http_address},
      http_port{default_http_port}
{
  astop.store(false);
}

void ApplicationContext::push_error(const std::string& errorDescription)
{
  errors.emplace_back(errorDescription);
}

bool ApplicationContext::stop() { return astop.load(); }

void ApplicationContext::stop(bool nstop) { astop.store(nstop); }

}  // namespace app
