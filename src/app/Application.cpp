#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/SDL2/SDL2Initer.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    return INVALID;
  }

  templateSDL2::SDL2Initer opengl;

  return opengl.run(ctx);
}

}  // namespace app
