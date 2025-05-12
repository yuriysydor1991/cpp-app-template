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

  const std::string& http_address();
  const unsigned short& http_port();

 protected:
  std::shared_ptr<app::ApplicationContext> actx;
};

}  // namespace beasthttp

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTEXT_CLASS_H
