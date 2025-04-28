#include "src/wt4/Wt4Context.h"

#include <cassert>
#include <memory>

namespace wt4server
{

Wt4Context::Wt4Context(std::shared_ptr<app::ApplicationContext> nAppCtx)
    : appctx{nAppCtx}
{
  assert(appctx != nullptr);
}

}  // namespace wt4server
