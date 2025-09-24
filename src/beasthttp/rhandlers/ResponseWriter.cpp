#include "src/beasthttp/rhandlers/ResponseWriter.h"

#include <memory>

#include "src/beasthttp/beast-includes.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"
#include "src/log/log.h"

namespace beasthttp::rhandlers
{

bool ResponseWriter::write_response(std::shared_ptr<HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);
  assert(sctx->socket != nullptr);

  if (sctx == nullptr || sctx->socket == nullptr) {
    LOGE("Invalid context pointer provided");
    return false;
  }

  if (sctx->socket == nullptr) {
    LOGE("No context socket available");
    return false;
  }

  sctx->response.prepare_payload();

  return http::write(*sctx->socket, sctx->response) > 0U;
}

}  // namespace beasthttp::rhandlers
