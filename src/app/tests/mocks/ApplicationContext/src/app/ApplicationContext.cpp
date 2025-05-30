#include "ApplicationContext.h"

#include <iostream>

namespace app
{

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : argc{gargc}, argv{gargv}
{
}

}  // namespace app
