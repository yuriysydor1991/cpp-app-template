#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/freeglut/FreeGlutIniter.h"
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

  templateFreeGlut::FreeGlutIniter opengl;

  if (opengl.run(ctx) != 0) {
    LOGE("The freeglut controller returned invalid status");
    return INVALID;
  }

  return 0;
}

}  // namespace app
