#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPSESSIONCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPSESSIONCONTEXT_CLASS_H

#include <memory>

#include "src/beasthttp/beast-includes.h"

namespace beasthttp::rhandlers
{

/**
 * @brief The single HTTP session class. Holds required info
 * with buffers and other objects to handle the single HTTP session.
 */
class HTTPSessionContext
{
 public:
  virtual ~HTTPSessionContext();
  HTTPSessionContext(std::shared_ptr<tcp::socket> nsocket);

  /// @brief The accepted socket through witch all the requests and responses
  /// will be passed
  std::shared_ptr<tcp::socket> socket;

  /// @brief The boost flat buffer to read the HTTP requests.
  boost::beast::flat_buffer buffer;

  /// @brief The parsed request by the Boost Beast HTTP server.
  http::request<http::string_body> request;

  /// @brief The response object which will contain assembled response page.
  http::response<http::string_body> response;

  /// @brief The Boost Beast error code if any for read and/or write operations.
  boost::beast::error_code ec;
};

}  // namespace beasthttp::rhandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPSESSIONCONTEXT_CLASS_H
