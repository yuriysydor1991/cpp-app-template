#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_DEFAULTHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_DEFAULTHANDLER_CLASS_H

#include <memory>

#include "src/beasthttp/rhandlers/HTTPSessionContext.h"
#include "src/beasthttp/rhandlers/IRequestHandler.h"

namespace beasthttp::rhandlers
{

/**
 * @brief The default HTTP session handler.
 * Shows a single simple web page with small message.
 */
class DefaultHandler : public IRequestHandler
{
 public:
  virtual ~DefaultHandler() = default;
  DefaultHandler() = default;

  virtual bool handle_session(
      std::shared_ptr<HTTPSessionContext> sctx) override;
};

}  // namespace beasthttp::rhandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DEFAULTHANDLER_CLASS_H
