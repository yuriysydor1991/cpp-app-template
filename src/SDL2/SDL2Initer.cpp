#include "src/SDL2/SDL2Initer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <cassert>
#include <stdexcept>

#include "project-global-decls.h"
#include "src/app/IApplication.h"

namespace templateSDL2
{

SDL2Initer::SDL2Initer() : painter3d{std::make_shared<painter::Painter>()} {}

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

  sdl2Context = std::make_shared<SDL2Context>(ctx);
  events = std::make_shared<events::EventsController>();

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
  assert(sdl2Context != nullptr);

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throw_sdl2("SDL could not initialize!");
    return false;
  }

  if (!set_opengl_attributes()) {
    return false;
  }

  sdl2Context->window = create_window();

  if (sdl2Context->window == nullptr) {
    throw_sdl2("Window could not be created!");
    return false;
  }

  sdl2Context->glContext = create_context();

  if (sdl2Context->glContext == nullptr) {
    throw_sdl2("OpenGL context could not be created!");
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

SDL_GLContext SDL2Initer::create_context()
{
  assert(sdl2Context->window != nullptr);

  if (sdl2Context->window == nullptr) {
    throw_sdl2("No window available to create context");
    return nullptr;
  }

  return SDL_GL_CreateContext(sdl2Context->window);
}

SDL_Window* SDL2Initer::create_window()
{
  return SDL_CreateWindow(get_window_title().c_str(), SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED, default_window_width,
                          default_window_height, get_create_window_flags());
}

const std::string& SDL2Initer::get_window_title()
{
  static const std::string windowTitle =
      project_decls::PROJECT_NAME + " " + project_decls::PROJECT_BUILD_VERSION;

  return windowTitle;
}

SDL_WindowFlags SDL2Initer::get_create_window_flags()
{
  return static_cast<SDL_WindowFlags>(SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
                                      SDL_WINDOW_RESIZABLE);
}

void SDL2Initer::throw_sdl2(const std::string& errDesc)
{
  throw std::runtime_error(errDesc + std::string{" SDL_Error: "} +
                           SDL_GetError());
}

}  // namespace templateSDL2
