#include "src/app/applications/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/SDL2/SDL2Controller.h"
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

  templateSDL2::SDL2Controller opengl;

  if (opengl.run(ctx) != 0) {
    LOGE("The SDL2 controller returned invalid state");
    return INVALID;
  }

  return 0;
}

}  // namespace app
