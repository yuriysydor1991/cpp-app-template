#include <memory>
#include <cassert>

#include "src/app/ApplicationContext.h"

#include "src/SDL2/SDL2Context.h"

namespace templateSDL2
{

SDL2Context::~SDL2Context()
{
  if (glContext != nullptr) {
    SDL_GL_DeleteContext(glContext);
    glContext = nullptr;
  }

  if (window != nullptr) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }
}

SDL2Context::SDL2Context(std::shared_ptr<app::ApplicationContext> ctx)
: appCtx{ctx}
{
  assert(appCtx != nullptr);
}

}  // namespace app
