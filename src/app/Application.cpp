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

  if (!opencv->load_cascade(ctx->cascade_path)) {
    LOGE("Failed to load the pre-installed Haar cascade. Provide the path "
         "explicitly with --face-cascade <path/to/haarcascade_frontalface_default.xml>");
    return INVALID;
  }

  LOGI("OpenCV face cascade loaded from " << opencv->get_cascade_path());

  if (ctx->image_path.empty()) {
    LOGI("No --image was provided, nothing to scan. The OpenCV face detection "
         "stack is initialised and ready.");
    return 0;
  }

  const auto faces = opencv->detect(ctx->image_path);

  LOGI("Detected " << faces.size() << " face(s) in " << ctx->image_path);

  return 0;
}

}  // namespace app
