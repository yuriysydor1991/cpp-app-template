#include "src/beasthttp/HttpController.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <cassert>
#include <iostream>
#include <memory>
#include <thread>

namespace beasthttp
{

bool HttpController::serve(std::shared_ptr<app::ApplicationContext> actx)
{
  assert(actx != nullptr);

  if (actx == nullptr) {
    return false;
  }

  mcontext = create_context(actx);

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
  try {
    boost::beast::flat_buffer buffer;

    http::request<http::string_body> request;
    http::read(*socket, buffer, request);

    http::response<http::string_body> response{http::status::ok,
                                               request.version()};

    response.set(http::field::server, "Template Project Beast Server");
    response.set(http::field::content_type, "text/html");
    response.keep_alive(false);

    response.body() =
        "<html><body><h1>Hello from C++ template project "
        "Boost.Beast!</h1></body></html>";

    response.prepare_payload();

    http::write(*socket, response);

    boost::beast::error_code ec;
    socket->shutdown(tcp::socket::shutdown_send, ec);
  }
  catch (const std::exception& e) {
    std::cerr << "Session error: " << e.what() << std::endl;
  }
}

}  // namespace beasthttp
