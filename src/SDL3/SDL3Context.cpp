#include "src/SDL3/SDL3Context.h"

#include <cassert>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace templateSDL3
{

SDL3Context::~SDL3Context()
{
  if (glContext != nullptr) {
    SDL_GL_DestroyContext(glContext);
    glContext = nullptr;
  }

  if (window != nullptr) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }
}

SDL3Context::SDL3Context(app::ApplicationContextPtr ctx) : appCtx{ctx}
{
  assert(appCtx != nullptr);
}

}  // namespace templateSDL3
