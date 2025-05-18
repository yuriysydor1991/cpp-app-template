#include "src/beasthttp/rhandlers/HandlersFactory.h"

#include <cassert>
#include <memory>

#include "src/beasthttp/rhandlers/DefaultHandler.h"

namespace beasthttp::rhandlers
{

std::shared_ptr<IRequestHandler> HandlersFactory::create_appropriate_handler(
    [[maybe_unused]] std::shared_ptr<HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  // register new http session handlers over here

  return std::make_shared<DefaultHandler>();
}

}  // namespace beasthttp::rhandlers
