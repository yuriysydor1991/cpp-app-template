#include "ApplicationContext.h"

namespace app
{

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : argc{gargc}, argv{gargv}, http_port{0}
{
}

}  // namespace app