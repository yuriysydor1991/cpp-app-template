#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTROLLER_CLASS_H

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/beasthttp/HttpContext.h"

namespace beasthttp
{

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

/**
 * @brief The controller class of the BoostBeast http server.
 * Starts the server in accordance with the provided info with
 * an appropriate request handlers.
 */
class HttpController
{
 public:
  virtual ~HttpController() = default;
  HttpController() = default;

  /**
   * @brief Start up the server with given context' info and
   * run appropriate request handler for each http request.
   */
  virtual bool serve(std::shared_ptr<app::ApplicationContext> actx);

 protected:
  virtual std::unique_ptr<HttpContext> create_context(
      std::shared_ptr<app::ApplicationContext> actx);

  virtual void handle_session(std::shared_ptr<tcp::socket> socket);

  std::unique_ptr<HttpContext> mcontext;
};

}  // namespace beasthttp

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTROLLER_CLASS_H
