#include "src/beasthttp/rhandlers/DefaultHandler.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/beasthttp/beast-includes.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"
#include "src/beasthttp/rhandlers/IRequestHandler.h"

namespace beasthttp::rhandlers
{

bool DefaultHandler::handle_session(std::shared_ptr<HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);
  assert(sctx->socket != nullptr);

  if (sctx == nullptr) {
    return false;
  }

  try {
    if (!build_response(sctx)) {
      return false;
    }

    sctx->response.body() =
        "<html><body><h1>Hello from C++ template project "
        "Boost.Beast!</h1></body></html>";

    sctx->response.prepare_payload();

    http::write(*sctx->socket, sctx->response);

    boost::beast::error_code ec;
    sctx->socket->shutdown(tcp::socket::shutdown_send, ec);
  }
  catch (const std::exception& e) {
    std::cerr << "Session error: " << e.what() << std::endl;
  }

  return true;
}

std::shared_ptr<ResponseBuilder> DefaultHandler::create_response_builder(
    [[maybe_unused]] std::shared_ptr<HTTPSessionContext> sctx)
{
  return std::make_shared<ResponseBuilder>();
}

bool DefaultHandler::build_response(std::shared_ptr<HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  auto rbuilder = create_response_builder(sctx);

  assert(rbuilder != nullptr);

  return rbuilder->build_response(sctx);
}

}  // namespace beasthttp::rhandlers
