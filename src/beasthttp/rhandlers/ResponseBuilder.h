#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_RESPONSEBUILDER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_RESPONSEBUILDER_CLASS_H

#include <memory>

#include "src/beasthttp/beast-includes.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"

namespace beasthttp::rhandlers
{

class ResponseBuilder
{
 public:
  virtual ~ResponseBuilder() = default;
  ResponseBuilder() = default;

  virtual bool build_response(std::shared_ptr<HTTPSessionContext> sctx);

 protected:
  virtual void set_defaults(std::shared_ptr<HTTPSessionContext> sctx);

  virtual const char* const& get_return_type();
  virtual bool get_keep_alive();
};

}  // namespace beasthttp::rhandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_RESPONSEBUILDER_CLASS_H
