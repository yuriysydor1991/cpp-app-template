#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SDL2CONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SDL2CONTEXT_CLASS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <memory>

#include "src/app/ApplicationContext.h"

namespace templateSDL2
{

struct SDL2Context
{
  virtual ~SDL2Context();
  SDL2Context(std::shared_ptr<app::ApplicationContext> ctx);

  std::shared_ptr<app::ApplicationContext> appCtx;

  SDL_Window* window{nullptr};
  SDL_GLContext glContext{nullptr};
};

}  // namespace templateSDL2

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SDL2CONTEXT_CLASS_H
