#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPSESSIONCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPSESSIONCONTEXT_CLASS_H

#include <memory>

#include "src/beasthttp/beast-includes.h"

namespace beasthttp::rhandlers
{

class HTTPSessionContext
{
 public:
  virtual ~HTTPSessionContext();
  HTTPSessionContext(std::shared_ptr<tcp::socket> nsocket);

  std::shared_ptr<tcp::socket> socket;

  boost::beast::flat_buffer buffer;
  http::request<http::string_body> request;

  http::response<http::string_body> response;

  boost::beast::error_code ec;
};

}  // namespace beasthttp::rhandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPSESSIONCONTEXT_CLASS_H
