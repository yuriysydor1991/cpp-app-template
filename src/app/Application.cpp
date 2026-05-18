#include "src/app/Application.h"

#include <cassert>
#include <memory>

#include "src/log/log.h"
#include "src/opencv/OpenCVController.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  auto opencv = opencvi::OpenCVController::create();

  assert(opencv != nullptr);

  if (opencv == nullptr) {
    LOGE("Failed to create the OpenCVController instance");
    return INVALID;
  }

  if (!opencv->run(ctx)) {
    LOGE("OpenCVController signalled about failure");
    return INVALID;
  }

  return 0;
}

}  // namespace app
