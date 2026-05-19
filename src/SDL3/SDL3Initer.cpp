#include "src/SDL3/SDL3Initer.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <cassert>
#include <stdexcept>

#include "project-global-decls.h"
#include "src/app/IApplication.h"
#include "src/log/log.h"

namespace templateSDL3
{

SDL3Initer::SDL3Initer()
    : ctxBuilder{std::make_shared<SDL3ContextBuilder>()},
      events{std::make_shared<events::EventsController>()},
      painter3d{std::make_shared<painter::Painter>()},
      oglIniter{std::make_shared<OpenGLIniter>()}
{
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    throw_sdl3("Fail to init the SDL3");
  }
}

SDL3Initer::~SDL3Initer()
{
  sdl3Context.reset();

  SDL_Quit();
}

int SDL3Initer::run(std::shared_ptr<app::ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid application context provied");
    return app::IApplication::INVALID;
  }

  sdl3Context = ctxBuilder->build_context(ctx);

  assert(sdl3Context != nullptr);

  if (sdl3Context == nullptr) {
    LOGE("Fail to create the SDL3 context");
    return app::IApplication::INVALID;
  }

  if (!oglIniter->init_opengl(sdl3Context)) {
    LOGE("Fail to initiate the OpenGL");
    return app::IApplication::INVALID;
  }

  event_loop();

  return 0;
}

void SDL3Initer::event_loop()
{
  assert(sdl3Context != nullptr);
  assert(sdl3Context->appCtx != nullptr);
  assert(events != nullptr);
  assert(painter3d != nullptr);

  if (sdl3Context == nullptr) {
    throw_sdl3("No SDL3Context given");
    return;
  }

  if (painter3d == nullptr) {
    throw_sdl3("No scene painter given");
    return;
  }

  if (events == nullptr) {
    throw_sdl3("No event handler given");
    return;
  }

  while (!sdl3Context->appCtx->stop()) {
    events->handle(sdl3Context);

    painter3d->paint(sdl3Context);

    SDL_GL_SwapWindow(sdl3Context->window);
  }
}

void SDL3Initer::throw_sdl3(const std::string& errDesc)
{
  LOGE(errDesc << std::string{" SDL_Error: "} << SDL_GetError());

  throw std::runtime_error(errDesc + std::string{" SDL_Error: "} +
                           SDL_GetError());
}

}  // namespace templateSDL3
