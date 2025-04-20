#include "src/SDL2/SDL2Initer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <cassert>
#include <stdexcept>

#include "project-global-decls.h"
#include "src/app/IApplication.h"

namespace templateSDL2
{

SDL2Initer::SDL2Initer()
    : ctxBuilder{std::make_shared<SDL2ContextBuilder>()},
      events{std::make_shared<events::EventsController>()},
      painter3d{std::make_shared<painter::Painter>()}
{
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
    return app::IApplication::INVALID;
  }

  sdl2Context = ctxBuilder->build_context(ctx);

  if (!init_opengl()) {
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

bool SDL2Initer::init_opengl()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throw_sdl2("SDL could not initialize!");
    return false;
  }

  if (!set_opengl_attributes()) {
    return false;
  }

  return true;
}

bool SDL2Initer::set_opengl_attributes()
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_CONTEXT_MAJOR_VERSION);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_CONTEXT_MINOR_VERSION);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  return true;
}

void SDL2Initer::throw_sdl2(const std::string& errDesc)
{
  throw std::runtime_error(errDesc + std::string{" SDL_Error: "} +
                           SDL_GetError());
}

}  // namespace templateSDL2
