#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTEXT_CLASS_H

#include <memory>

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
  HttpContext(std::shared_ptr<app::ApplicationContext> nactx);

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
  const std::string& http_address();

  /**
   * @brief Returns the port that will be used to start the HTTP server.
   *
   * @return Returns HTTP server desired port number.
   */
  const unsigned short& http_port();

 protected:
  std::shared_ptr<app::ApplicationContext> actx;
};

}  // namespace beasthttp

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTEXT_CLASS_H
