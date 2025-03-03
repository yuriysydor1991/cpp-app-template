#include "src/app/ApplicationContext.h"

namespace app {

ApplicationContext::ApplicationContext(int& gargc, char** &gargv)
  : argc{gargc}, argv{gargv}
{}

} // namespace app
