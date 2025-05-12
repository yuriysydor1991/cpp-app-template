#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/beasthttp/HttpController.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    return INVALID;
  }

  auto http = std::make_shared<beasthttp::HttpController>();

  if (!http->serve(ctx)) {
    return INVALID;
  }

  return 0;
}

}  // namespace app
