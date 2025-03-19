#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/freeglut/FreeGlutIniter.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    return INVALID;
  }

  templateFreeGlut::FreeGlutIniter opengl;

  return opengl.run(ctx);
}

}  // namespace app
