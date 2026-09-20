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

HttpControllerPtr HttpController::create()
{
  return std::make_shared<HttpController>();
}

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

    acceptor.listen(mcontext->listen_backlog());

    LOGI("Listening on http://" << mcontext->http_address() << ":"
                                << mcontext->http_port());

    while (!mcontext->stop()) {
      auto sctx = create_http_session_context();

      acceptor.accept(sctx->stream->socket());

      clean_threads();

      if (sessions_limit_reached()) {
        LOGW("Dropping the accepted connection: already serving the allowed "
             << mcontext->max_connections() << " ones");
        continue;
      }

      auto future = std::make_shared<std::future<bool>>(std::async(
          std::launch::async, [this, sctx]() { return handle_session(sctx); }));

      handlersThs.insert(future);

      LOGT("Handling sessions: " << handlersThs.size());
    }

    LOGD("Waiting remaining threads to be finished");
    wait_threads();
  }
  catch (const std::exception& e) {
    LOGE("Server error: " << e.what());
    return false;
  }

  return true;
}

void HttpController::clean_threads()
{
  LOGD("Cleaning ready handlers");

  auto titer = handlersThs.begin();

  while (titer != handlersThs.end()) {
    auto& th = *titer;
    if (th->wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
      titer = handlersThs.erase(titer);
      continue;
    }

    ++titer;
  }
}

void HttpController::wait_threads()
{
  LOGD("Waiting for all handlers to finish");

  for (auto& th : handlersThs) {
    th->wait();
  }

  handlersThs.clear();
}

std::unique_ptr<HttpContext> HttpController::create_context(
    std::shared_ptr<app::ApplicationContext> actx)
{
  assert(actx != nullptr);

  return std::make_unique<HttpContext>(actx);
}

std::shared_ptr<rhandlers::HTTPSessionContext>
HttpController::create_http_session_context()
{
  return std::make_shared<rhandlers::HTTPSessionContext>();
}

bool HttpController::sessions_limit_reached() const
{
  assert(mcontext != nullptr);

  return handlersThs.size() >= mcontext->max_connections();
}

bool HttpController::handle_session(
    std::shared_ptr<rhandlers::HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);
  assert(rhFactory != nullptr);
  assert(mcontext != nullptr);

  if (sctx == nullptr) {
    LOGE("Invalid context pointer provided");
    return false;
  }

  auto handler = rhFactory->create_appropriate_handler(sctx);

  assert(handler != nullptr);

  if (handler == nullptr) {
    LOGE("Fail to create appropriate session handler");
    return false;
  }

  /// @todo: make session requests read in cycle to recycle the connection
  handler->handle_session(sctx);

  // The connection is released here and not by the context destructor, since
  // the started session keeps it's context alive until the finished handler
  // is reaped by the clean_threads call.
  sctx->close();

  return true;
}

}  // namespace beasthttp
