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

  return actx == nullptr || actx->stop();
}

const std::string& HttpContext::http_address() const
{
  return actx->http_address;
}

const unsigned short& HttpContext::http_port() const { return actx->http_port; }

}  // namespace beasthttp
