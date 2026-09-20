#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTEXT_CLASS_H

#include <memory>

#include "project-global-decls.h"
#include "src/app/ApplicationContext.h"

namespace beasthttp
{

/**
 * @brief The HTTP server general context to hold all queues info etc.
 */
class HttpContext
{
 public:
  virtual ~HttpContext() = default;
  explicit HttpContext(std::shared_ptr<app::ApplicationContext> nactx);

  /**
   * @brief Returns the application context stop method return value.
   */
  bool stop();

  /**
   * @brief the method to retrieve the used HTTP address specified
   * in the contained app::ApplicationContext instance.
   *
   * @return Returns the specified HTTP address for the HTTP server
   * start up.
   */
  const std::string& http_address() const;

  /**
   * @brief Returns the port that will be used to start the HTTP server.
   *
   * @return Returns HTTP server desired port number.
   */
  unsigned short http_port() const;

  /**
   * @brief The number of the connections the server serves at once. The
   * accepted connection above it is dropped right away, so no client crowd
   * grows the thread count of the server without a bound.
   *
   * @return Returns the maximum number of the simultaneously served HTTP
   * connections.
   */
  unsigned int max_connections() const;

  /**
   * @brief The length of the queue the OS fills with the connections that
   * are established but not accepted yet.
   *
   * @return Returns the listen backlog of the server socket.
   */
  int listen_backlog() const;

 protected:
  std::shared_ptr<app::ApplicationContext> actx;

  /// @brief The number of the connections served at once. Lower it in the
  /// descendant constructor to harden the server further.
  unsigned int mmax_connections{project_decls::PROJECT_HTTP_MAX_CONNECTIONS};

  /// @brief The length of the queue of the connections waiting to be
  /// accepted. Lower it in the descendant constructor to harden the server
  /// further.
  int mlisten_backlog{project_decls::PROJECT_HTTP_LISTEN_BACKLOG};
};

}  // namespace beasthttp

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTEXT_CLASS_H
