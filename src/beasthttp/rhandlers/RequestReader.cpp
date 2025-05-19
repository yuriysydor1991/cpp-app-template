#include "src/beasthttp/rhandlers/RequestReader.h"

#include <cassert>
#include <memory>

namespace beasthttp::rhandlers
{

bool RequestReader::read_request(std::shared_ptr<HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);
  assert(sctx->socket != nullptr);

  if (sctx == nullptr) {
    return false;
  }

  if (sctx->socket == nullptr) {
    return false;
  }

  return http::read(*sctx->socket, sctx->buffer, sctx->request) > 0U;
}

}  // namespace beasthttp::rhandlers
