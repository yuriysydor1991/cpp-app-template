#include "src/beasthttp/HttpContext.h"

#include <cassert>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace beasthttp
{

HttpContext::HttpContext(std::shared_ptr<app::ApplicationContext> nactx)
    : actx{nactx}
{
  assert(actx != nullptr);
}

bool HttpContext::stop()
{
  assert(actx != nullptr);

  return actx == nullptr || actx->get_stop();
}

const std::string& HttpContext::http_address() const
{
  return actx->get_http_address();
}

unsigned short HttpContext::http_port() const { return actx->get_http_port(); }

}  // namespace beasthttp
