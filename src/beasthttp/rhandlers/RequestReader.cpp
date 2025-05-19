#include "src/beasthttp/rhandlers/RequestReader.h"

#include <cassert>
#include <iostream>
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

  bool readRes{false};

  try {
    readRes = http::read(*sctx->socket, sctx->buffer, sctx->request) > 0U;
  }
  catch (const std::exception& e) {
    std::cerr << "Session error: " << e.what() << std::endl;
  }

  return readRes;
}

}  // namespace beasthttp::rhandlers
