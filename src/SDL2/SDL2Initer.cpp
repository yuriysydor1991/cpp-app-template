#include "src/SDL2/SDL2Initer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <cassert>
#include <stdexcept>

#include "project-global-decls.h"
#include "src/app/IApplication.h"

namespace templateSDL2
{

SDL2Initer::~SDL2Initer()
{
  if (window != nullptr) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }

  if (glContext != nullptr) {
    SDL_GL_DeleteContext(glContext);
    glContext = nullptr;
  }

  SDL_Quit();
}

void SDL2Initer::draw_3D_scene()
{
  glClear(GL_COLOR_BUFFER_BIT);

  // put the OpenGL draw scene over here
}

void SDL2Initer::parse_event(SDL_Event& event)
{
  assert(mAppCtx != nullptr);

  if (mAppCtx == nullptr) {
    return;
  }

  if (event.type == SDL_QUIT) {
    mAppCtx->stop(true);
  }

  // put other event types parse here
}

int SDL2Initer::run(std::shared_ptr<app::ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    return app::IApplication::INVALID;
  }

  mAppCtx = ctx;

  if (!init_opengl()) {
    return app::IApplication::INVALID;
  }

  event_loop();

  return 0;
}

void SDL2Initer::event_loop()
{
  while (!mAppCtx->stop()) {
    eventer();

    draw_3D_scene();

    SDL_GL_SwapWindow(window);
  }
}

void SDL2Initer::eventer()
{
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    parse_event(event);
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

  window = create_window();

  if (window == nullptr) {
    throw_sdl2("Window could not be created!");
    return false;
  }

  glContext = create_context();

  if (glContext == nullptr) {
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
  assert(window != nullptr);

  if (window == nullptr) {
    return nullptr;
  }

  return SDL_GL_CreateContext(window);
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
