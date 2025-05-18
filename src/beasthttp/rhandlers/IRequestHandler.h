#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IREQUESTHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IREQUESTHANDLER_CLASS_H

#include <memory>

#include "src/beasthttp/beast-includes.h"

/**
 * @brief The HTTP session handlers component namespace.
 */
namespace beasthttp::rhandlers
{

/**
 * @brief The abstract class to create an interface for the HTTP sessions
 * handlers.
 */
class IRequestHandler
{
 public:
  virtual ~IRequestHandler() = default;
  IRequestHandler() = default;

  /**
   * @brief Handle all the request for the given HTTP session context.
   *
   * @param sctx Filled context with a socket and other necessary info.
   *
   * @returns A true boolean value on the success and false otherwise.
   */
  virtual bool handle_session(std::shared_ptr<HTTPSessionContext> sctx) = 0;
};

}  // namespace beasthttp::rhandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IREQUESTHANDLER_CLASS_H
