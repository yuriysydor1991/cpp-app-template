#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_REQUESTREADER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_REQUESTREADER_CLASS_H

#include <memory>

#include "src/beasthttp/beast-includes.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"

namespace beasthttp::rhandlers
{

class RequestReader
{
 public:
  virtual ~RequestReader() = default;
  RequestReader() = default;

  virtual bool read_request(std::shared_ptr<HTTPSessionContext> sctx);
};

}  // namespace beasthttp::rhandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_REQUESTREADER_CLASS_H
