#include "src/SDL2/SDL2Initer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <cassert>
#include <stdexcept>

#include "project-global-decls.h"
#include "src/app/IApplication.h"
#include "src/log/log.h"

namespace templateSDL2
{

SDL2Initer::SDL2Initer()
    : ctxBuilder{std::make_shared<SDL2ContextBuilder>()},
      events{std::make_shared<events::EventsController>()},
      painter3d{std::make_shared<painter::Painter>()},
      oglIniter{std::make_shared<OpenGLIniter>()}
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throw_sdl2("Fail to init the SDL2");
  }
}

SDL2Initer::~SDL2Initer()
{
  sdl2Context.reset();

  SDL_Quit();
}

int SDL2Initer::run(std::shared_ptr<app::ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid application context provied");
    return app::IApplication::INVALID;
  }

  sdl2Context = ctxBuilder->build_context(ctx);

  assert(sdl2Context != nullptr);

  if (sdl2Context == nullptr) {
    LOGE("Fail to create the SDL2 context");
    return app::IApplication::INVALID;
  }

  if (!oglIniter->init_opengl(sdl2Context)) {
    LOGE("Fail to initiate the OpenGL");
    return app::IApplication::INVALID;
  }

  event_loop();

  return 0;
}

void SDL2Initer::event_loop()
{
  assert(sdl2Context != nullptr);
  assert(sdl2Context->appCtx != nullptr);
  assert(events != nullptr);
  assert(painter3d != nullptr);

  if (sdl2Context == nullptr) {
    throw_sdl2("No SDL2Context given");
    return;
  }

  if (painter3d == nullptr) {
    throw_sdl2("No scene painter given");
    return;
  }

  if (events == nullptr) {
    throw_sdl2("No event handler given");
    return;
  }

  while (!sdl2Context->appCtx->stop()) {
    events->handle(sdl2Context);

    painter3d->paint(sdl2Context);

    SDL_GL_SwapWindow(sdl2Context->window);
  }
}

void SDL2Initer::throw_sdl2(const std::string& errDesc)
{
  LOGE(errDesc << std::string{" SDL_Error: "} << SDL_GetError());

  throw std::runtime_error(errDesc + std::string{" SDL_Error: "} +
                           SDL_GetError());
}

}  // namespace templateSDL2
