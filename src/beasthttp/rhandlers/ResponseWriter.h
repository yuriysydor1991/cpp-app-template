#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_RESPONSEWRITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_RESPONSEWRITER_CLASS_H

#include <memory>

#include "src/beasthttp/beast-includes.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"

namespace beasthttp::rhandlers
{

class ResponseWriter
{
 public:
  virtual ~ResponseWriter() = default;
  ResponseWriter() = default;

  virtual bool write_response(std::shared_ptr<HTTPSessionContext> sctx);
};

}  // namespace beasthttp::rhandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_RESPONSEWRITER_CLASS_H
