#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_HANDLERSFACTORY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_HANDLERSFACTORY_CLASS_H

#include <memory>

#include "src/beasthttp/beast-includes.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"
#include "src/beasthttp/rhandlers/IRequestHandler.h"

namespace beasthttp::rhandlers
{

class HandlersFactory
{
 public:
  virtual ~HandlersFactory() = default;
  HandlersFactory() = default;

  virtual std::shared_ptr<IRequestHandler> create_appropriate_handler(
      std::shared_ptr<HTTPSessionContext> sctx);
};

}  // namespace beasthttp::rhandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HANDLERSFACTORY_CLASS_H
