#include "src/beasthttp/rhandlers/HTTPSessionContext.h"

#include <memory>

#include "src/beasthttp/beast-includes.h"

namespace beasthttp::rhandlers
{

HTTPSessionContext::~HTTPSessionContext() { close(); }

void HTTPSessionContext::close()
{
  if (stream == nullptr) {
    return;
  }

  stream->socket().shutdown(tcp::socket::shutdown_send, ec);
  stream->close();
}

HTTPSessionContext::HTTPSessionContext()
    : ioc{std::make_shared<boost::asio::io_context>(1)},
      stream{std::make_shared<boost::beast::tcp_stream>(*ioc)}
{
}

}  // namespace beasthttp::rhandlers
