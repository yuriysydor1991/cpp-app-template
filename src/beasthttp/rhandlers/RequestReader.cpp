#include "src/beasthttp/rhandlers/RequestReader.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/log/log.h"

namespace beasthttp::rhandlers
{

bool RequestReader::read_request(std::shared_ptr<HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);
  assert(sctx->socket != nullptr);

  if (sctx == nullptr) {
    LOGE("Invalid context pointer provided");
    return false;
  }

  if (sctx->socket == nullptr) {
    LOGE("No socket available");
    return false;
  }

  bool readRes{false};

  try {
    readRes = http::read(*sctx->socket, sctx->buffer, sctx->request) > 0U;
  }
  catch (const std::exception& e) {
    LOGE("Session error: " << e.what());
    return false;
  }

  return readRes;
}

}  // namespace beasthttp::rhandlers
