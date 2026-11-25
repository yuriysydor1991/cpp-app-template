#include "src/app/applications/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/log/log.h"

namespace app
{

int Application::run(ApplicationContextPtr ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  LOGI("Your application implementation goes here!");

  return 0;
}

}  // namespace app
