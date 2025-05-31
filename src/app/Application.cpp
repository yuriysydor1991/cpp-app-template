#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/beasthttp/HttpController.h"
#include "src/log/log.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  auto http = std::make_shared<beasthttp::HttpController>();

  if (!http->serve(ctx)) {
    LOGE("The HTTP server returned an invalid status");
    return INVALID;
  }

  return 0;
}

}  // namespace app
