#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTROLLER_CLASS_H

#include <future>
#include <memory>
#include <unordered_set>

#include "src/app/ApplicationContext.h"
#include "src/beasthttp/HttpContext.h"
#include "src/beasthttp/beast-includes.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"
#include "src/beasthttp/rhandlers/HandlersFactory.h"

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
  using HttpControllerPtr = std::shared_ptr<HttpController>;

  virtual ~HttpController();
  HttpController() = default;

  /**
   * @brief Start up the server with given context' info and
   * run appropriate request handler for each http request.
   *
   * @param actx The app::ApplicationContext instance with info
   * to provide all required information in order to start the HTTP server
   * instance.
   *
   * @return Returns a true boolean value on the success and false otherwise.
   */
  virtual bool serve(std::shared_ptr<app::ApplicationContext> actx);

  static HttpControllerPtr create();

 protected:
  /**
   * @brief Creates the HTTP server context instance to hold
   * the data of interest.
   *
   * @param actx The app::ApplicationContext instance with the required info.
   *
   * @return Returns filled HttpContext class instance in case of success.
   */
  virtual std::unique_ptr<HttpContext> create_context(
      std::shared_ptr<app::ApplicationContext> actx);

  /**
   * @brief Creates the rhandlers::HTTPSessionContext class instance to
   * accept the next connection into and to provide it to the HTTP session
   * handler afterwards. Override it in the descendant to lower the hardening
   * constraints the created context carries.
   *
   * @return Returns the rhandlers::HTTPSessionContext instance to pass to
   * the session handler.
   */
  virtual std::shared_ptr<rhandlers::HTTPSessionContext>
  create_http_session_context();

  /**
   * @brief The new session starter routine. Creates the appropriate session
   * handler for the given context and calls it's handle_session method.
   *
   * @param sctx The context holding the accepted connection through which the
   * HTTP requests and HTTP responses will be transferred.
   */
  virtual bool handle_session(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  /**
   * @brief Tells whether the server serves as many connections at once as
   * it's context allows, so the next accepted one has to be dropped.
   *
   * @return Returns a true boolean value when no new session may be started.
   */
  virtual bool sessions_limit_reached() const;

  void wait_threads();
  void clean_threads();

  std::unique_ptr<HttpContext> mcontext;
  std::shared_ptr<rhandlers::HandlersFactory> rhFactory;

  std::unordered_set<std::shared_ptr<std::future<bool>>> handlersThs;
};

using HttpControllerPtr = HttpController::HttpControllerPtr;

}  // namespace beasthttp

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTROLLER_CLASS_H
