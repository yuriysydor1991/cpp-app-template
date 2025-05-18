#include "src/beasthttp/HttpController.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <cassert>
#include <iostream>
#include <memory>
#include <thread>

#include "src/beasthttp/rhandlers/HTTPSessionContext.h"

namespace beasthttp
{

bool HttpController::serve(std::shared_ptr<app::ApplicationContext> actx)
{
  assert(actx != nullptr);

  if (actx == nullptr) {
    return false;
  }

  mcontext = create_context(actx);
  rhFactory = std::make_shared<rhandlers::HandlersFactory>();

  try {
    const auto address =
        boost::asio::ip::make_address(mcontext->http_address());
    const unsigned short port = mcontext->http_port();

    boost::asio::io_context ioc{1};
    tcp::acceptor acceptor{ioc, {address, port}};

    std::cout << "Listening on http://" << mcontext->http_address() << ":"
              << mcontext->http_port() << std::endl;

    while (!mcontext->stop()) {
      auto socket = std::make_shared<tcp::socket>(ioc);
      acceptor.accept(*socket);

      std::thread{[this, socket]() { handle_session(socket); }}.detach();
    }
  }
  catch (const std::exception& e) {
    std::cerr << "Server error: " << e.what() << std::endl;
    return false;
  }

  return true;
}

std::unique_ptr<HttpContext> HttpController::create_context(
    std::shared_ptr<app::ApplicationContext> actx)
{
  assert(actx != nullptr);

  return std::make_unique<HttpContext>(actx);
}

void HttpController::handle_session(std::shared_ptr<tcp::socket> socket)
{
  assert(socket != nullptr);
  assert(rhFactory != nullptr);
  assert(mcontext != nullptr);

  if (socket == nullptr) {
    return;
  }

  auto sctx = std::make_shared<rhandlers::HTTPSessionContext>(socket);

  auto handler = rhFactory->create_appropriate_handler(sctx);

  assert(handler != nullptr);

  if (handler == nullptr) {
    return;
  }

  handler->handle_session(sctx);
}

}  // namespace beasthttp
