#include "src/SDL2/SDL2ContextBuilder.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <cassert>
#include <memory>

#include "project-global-decls.h"
#include "src/SDL2/SDL2Context.h"
#include "src/app/ApplicationContext.h"

namespace templateSDL2
{

std::shared_ptr<SDL2Context> SDL2ContextBuilder::build_context(
    std::shared_ptr<app::ApplicationContext> ctx)
{
  std::shared_ptr<SDL2Context> sdl2ctx = default_context(ctx);

  sdl2ctx->window = create_window(sdl2ctx);

  if (sdl2ctx->window == nullptr) {
    return {};
  }

  sdl2ctx->glContext = create_context(sdl2ctx);

  if (sdl2ctx->glContext == nullptr) {
    return {};
  }

  return sdl2ctx;
}

std::shared_ptr<SDL2Context> SDL2ContextBuilder::default_context(
    std::shared_ptr<app::ApplicationContext> ctx)
{
  return std::make_shared<SDL2Context>(ctx);
}

SDL_GLContext SDL2ContextBuilder::create_context(
    std::shared_ptr<SDL2Context> sdl2ctx)
{
  assert(sdl2ctx->window != nullptr);

  if (sdl2ctx->window == nullptr) {
    return nullptr;
  }

  return SDL_GL_CreateContext(sdl2ctx->window);
}

SDL_Window* SDL2ContextBuilder::create_window(
    [[maybe_unused]] std::shared_ptr<SDL2Context> sdl2ctx)
{
  return SDL_CreateWindow(get_window_title().c_str(), SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED, default_window_width,
                          default_window_height, get_create_window_flags());
}

const std::string& SDL2ContextBuilder::get_window_title()
{
  static const std::string windowTitle =
      project_decls::PROJECT_NAME + " " + project_decls::PROJECT_BUILD_VERSION;

  return windowTitle;
}

SDL_WindowFlags SDL2ContextBuilder::get_create_window_flags()
{
  return static_cast<SDL_WindowFlags>(SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
                                      SDL_WINDOW_RESIZABLE);
}

}  // namespace templateSDL2
