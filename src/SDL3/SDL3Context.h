#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SDL3CONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SDL3CONTEXT_CLASS_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <memory>

#include "src/app/ApplicationContext.h"

namespace templateSDL3
{

struct SDL3Context
{
  virtual ~SDL3Context();
  explicit SDL3Context(std::shared_ptr<app::ApplicationContext> ctx);

  std::shared_ptr<app::ApplicationContext> appCtx;

  SDL_Window* window{nullptr};
  SDL_GLContext glContext{nullptr};
};

}  // namespace templateSDL3

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SDL3CONTEXT_CLASS_H
