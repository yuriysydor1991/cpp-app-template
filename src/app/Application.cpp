#include "src/app/Application.h"

#include <cassert>
#include <memory>

#include "src/log/log.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid application context pointer provided")
    return INVALID;
  }

  LOGI("Your application implementation goes here!");

  return 0;
}

}  // namespace app
