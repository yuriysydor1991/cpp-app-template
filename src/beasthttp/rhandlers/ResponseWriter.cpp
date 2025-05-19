#include "src/beasthttp/rhandlers/ResponseWriter.h"

#include <memory>

#include "src/beasthttp/beast-includes.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"

namespace beasthttp::rhandlers
{

bool ResponseWriter::write_response(std::shared_ptr<HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);
  assert(sctx->socket != nullptr);

  sctx->response.prepare_payload();

  return http::write(*sctx->socket, sctx->response) > 0U;
}

}  // namespace beasthttp::rhandlers
