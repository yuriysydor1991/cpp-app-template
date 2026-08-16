#include "ApplicationContext.h"

#include <iostream>

namespace app
{

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : margc{gargc}, margv{gargv}
{
}

}  // namespace app
