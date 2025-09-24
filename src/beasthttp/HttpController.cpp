#include "src/beasthttp/HttpController.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <cassert>
#include <iostream>
#include <memory>
#include <thread>

#include "src/log/log.h"

namespace beasthttp
{

HttpController::~HttpController() { wait_threads(); }

bool HttpController::serve(std::shared_ptr<app::ApplicationContext> actx)
{
  assert(actx != nullptr);

  if (actx == nullptr) {
    LOGE("Invalid context pointer provided");
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

    LOGI("Listening on http://" << mcontext->http_address() << ":"
                                << mcontext->http_port());

    while (!mcontext->stop()) {
      auto socket = std::make_shared<tcp::socket>(ioc);
      acceptor.accept(*socket);

      handlersThs.insert(std::make_shared<std::thread>(
          [this, socket]() { handle_session(socket); }));

      clear_threads();
    }

    wait_threads();
  }
  catch (const std::exception& e) {
    LOGE("Server error: " << e.what());
    return false;
  }

  return true;
}

void HttpController::clear_threads()
{
  LOGD("Clearing empty handler thread");

  auto titer = handlersThs.begin();

  while (titer != handlersThs.end()) {
    auto& th = *titer;
    if (!th->joinable()) {
      titer = handlersThs.erase(titer);
      continue;
    }

    ++titer;
  }
}

void HttpController::wait_threads()
{
  LOGD("Waiting for all threads to finish");

  for (auto& th : handlersThs) {
    if (th->joinable()) {
      th->join();
    }
  }
}

std::unique_ptr<HttpContext> HttpController::create_context(
    std::shared_ptr<app::ApplicationContext> actx)
{
  assert(actx != nullptr);

  return std::make_unique<HttpContext>(actx);
}

std::shared_ptr<rhandlers::HTTPSessionContext>
HttpController::create_http_session_context(std::shared_ptr<tcp::socket> socket)
{
  return std::make_shared<rhandlers::HTTPSessionContext>(socket);
}

void HttpController::handle_session(std::shared_ptr<tcp::socket> socket)
{
  assert(socket != nullptr);
  assert(rhFactory != nullptr);
  assert(mcontext != nullptr);

  if (socket == nullptr) {
    LOGE("Invalid socket pointer provided");
    return;
  }

  auto sctx = create_http_session_context(socket);

  auto handler = rhFactory->create_appropriate_handler(sctx);

  assert(handler != nullptr);

  if (handler == nullptr) {
    LOGE("Fail to create appropriate session handler");
    return;
  }

  handler->handle_session(sctx);
}

}  // namespace beasthttp
