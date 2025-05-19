#include "src/beasthttp/pages/PageBuilder.h"

#include <cassert>
#include <memory>

#include "src/beasthttp/pages/IPageBuilder.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"

namespace beasthttp::pages
{

bool PageBuilder::build_request_page(
    std::shared_ptr<rhandlers::HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  if (sctx == nullptr) {
    return false;
  }

  auto& body = sctx->response.body();

  body =
      "<html><body><h1>Hello from C++ template project "
      "Boost.Beast!</h1></body></html>";

  return true;
}

}  // namespace beasthttp::pages
