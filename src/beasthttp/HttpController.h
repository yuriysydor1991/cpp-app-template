#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTROLLER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/beasthttp/HttpContext.h"
#include "src/beasthttp/beast-includes.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"
#include "src/beasthttp/rhandlers/HandlersFactory.h"
#include "src/beasthttp/rhandlers/RequestReader.h"

namespace beasthttp
{

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
  virtual std::shared_ptr<rhandlers::HTTPSessionContext>
  create_http_session_context(std::shared_ptr<tcp::socket> socket);
  virtual std::shared_ptr<rhandlers::RequestReader> create_request_reader(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  virtual bool read_single_request(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);
  virtual void handle_session(std::shared_ptr<tcp::socket> socket);

  std::unique_ptr<HttpContext> mcontext;
  std::shared_ptr<rhandlers::HandlersFactory> rhFactory;
};

}  // namespace beasthttp

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTROLLER_CLASS_H
