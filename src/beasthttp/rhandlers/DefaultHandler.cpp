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

  if (sctx == nullptr) {
    return false;
  }

  try {
    boost::beast::flat_buffer buffer;

    http::request<http::string_body> request;
    http::read(*sctx->socket, buffer, request);

    http::response<http::string_body> response{http::status::ok,
                                               request.version()};

    response.set(http::field::server, "Template Project Beast Server");
    response.set(http::field::content_type, "text/html");
    response.keep_alive(false);

    response.body() =
        "<html><body><h1>Hello from C++ template project "
        "Boost.Beast!</h1></body></html>";

    response.prepare_payload();

    http::write(*sctx->socket, response);

    boost::beast::error_code ec;
    sctx->socket->shutdown(tcp::socket::shutdown_send, ec);
  }
  catch (const std::exception& e) {
    std::cerr << "Session error: " << e.what() << std::endl;
  }

  return true;
}

}  // namespace beasthttp::rhandlers
