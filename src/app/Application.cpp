#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/SDL2/SDL2Initer.h"
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

  templateSDL2::SDL2Initer opengl;

  if (opengl.run(ctx) != 0) {
    LOGE("The SDL2 controller returned invalid state");
    return INVALID;
  }

  return 0;
}

}  // namespace app
