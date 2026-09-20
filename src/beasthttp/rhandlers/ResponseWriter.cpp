#include "src/beasthttp/rhandlers/ResponseWriter.h"

#include <cassert>
#include <cstddef>
#include <memory>

#include "src/beasthttp/beast-includes.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"
#include "src/log/log.h"

namespace beasthttp::rhandlers
{

bool ResponseWriter::write_response(std::shared_ptr<HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);
  assert(sctx->stream != nullptr);

  if (sctx == nullptr || sctx->stream == nullptr) {
    LOGE("Invalid context pointer provided");
    return false;
  }

  sctx->response.prepare_payload();

  std::size_t writtenBytes{0U};

  // The timeout is the Boost.Beast stream own one, since a blocking socket
  // call honors none and would leave the thread of the session waiting for a
  // client that stopped reading the answer it has asked for.
  sctx->stream->expires_after(sctx->responseTimeout);

  // The serializer overload of the write is the one taking no defaulted
  // pointer argument, so it raises no null pointer constant warning of the
  // strict compile options.
  http::response_serializer<http::string_body> serializer{sctx->response};

  http::async_write(*sctx->stream, serializer,
                    [&sctx, &writtenBytes](const boost::beast::error_code& nec,
                                           const std::size_t bytes) {
                      sctx->ec = nec;
                      writtenBytes = bytes;
                    });

  sctx->ioc->restart();
  sctx->ioc->run();

  if (sctx->ec) {
    LOGE("Fail to write the response: " << sctx->ec.message());
    return false;
  }

  return writtenBytes > 0U;
}

}  // namespace beasthttp::rhandlers
