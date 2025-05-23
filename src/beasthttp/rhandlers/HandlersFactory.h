#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_HANDLERSFACTORY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_HANDLERSFACTORY_CLASS_H

#include <memory>

#include "src/beasthttp/beast-includes.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"
#include "src/beasthttp/rhandlers/IRequestHandler.h"

namespace beasthttp::rhandlers
{

/**
 * @brief The HTTP session handlers factory.
 */
class HandlersFactory
{
 public:
  virtual ~HandlersFactory() = default;
  HandlersFactory() = default;

  /**
   * @brief Creates appropriate HTTP session handler object with
   * accordance of the provided data. The default implementation
   * returns the DefaultHandler class instance.
   *
   * @param sctx The single HTTP session context.
   *
   * @return Returns appropriate single HTTP session handler object
   * in case of success.
   */
  virtual std::shared_ptr<IRequestHandler> create_appropriate_handler(
      std::shared_ptr<HTTPSessionContext> sctx);
};

}  // namespace beasthttp::rhandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HANDLERSFACTORY_CLASS_H
