#include "src/beasthttp/rhandlers/RequestReader.h"

#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>

#include "src/log/log.h"

namespace beasthttp::rhandlers
{

bool RequestReader::read_request(std::shared_ptr<HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);
  assert(sctx->stream != nullptr);

  if (sctx == nullptr) {
    LOGE("Invalid context pointer provided");
    return false;
  }

  if (sctx->stream == nullptr) {
    LOGE("No stream available");
    return false;
  }

  try {
    http::request_parser<http::string_body> parser;

    parser.header_limit(sctx->maxHeaderBytes);
    parser.body_limit(sctx->maxBodyBytes);

    if (!read_into(sctx, parser)) {
      return false;
    }

    sctx->request = parser.release();
  }
  catch (const std::exception& e) {
    LOGE("Session error: " << e.what());
    return false;
  }

  return true;
}

bool RequestReader::read_into(std::shared_ptr<HTTPSessionContext> sctx,
                              http::request_parser<http::string_body>& parser)
{
  assert(sctx != nullptr);

  std::size_t readBytes{0U};

  // The timeout is the Boost.Beast stream own one, since a blocking socket
  // call honors none and would leave the thread of the session waiting for a
  // client that sends nothing.
  sctx->stream->expires_after(sctx->requestTimeout);

  http::async_read(*sctx->stream, sctx->buffer, parser,
                   [&sctx, &readBytes](const boost::beast::error_code& nec,
                                       const std::size_t bytes) {
                     sctx->ec = nec;
                     readBytes = bytes;
                   });

  sctx->ioc->restart();
  sctx->ioc->run();

  if (sctx->ec) {
    LOGE("Fail to read the request: " << sctx->ec.message());
    return false;
  }

  return readBytes > 0U;
}

}  // namespace beasthttp::rhandlers
