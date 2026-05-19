#include "src/SDL3/SDL3ContextBuilder.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <cassert>
#include <memory>

#include "project-global-decls.h"
#include "src/SDL3/SDL3Context.h"
#include "src/app/ApplicationContext.h"
#include "src/log/log.h"

namespace templateSDL3
{

std::shared_ptr<SDL3Context> SDL3ContextBuilder::build_context(
    std::shared_ptr<app::ApplicationContext> ctx)
{
  std::shared_ptr<SDL3Context> sdl3ctx = default_context(ctx);

  sdl3ctx->window = create_window(sdl3ctx);

  if (sdl3ctx->window == nullptr) {
    LOGE("No window object pointer provided");
    return {};
  }

  sdl3ctx->glContext = create_context(sdl3ctx);

  if (sdl3ctx->glContext == nullptr) {
    LOGE("No OpenGL context object pointer provided");
    return {};
  }

  return sdl3ctx;
}

std::shared_ptr<SDL3Context> SDL3ContextBuilder::default_context(
    std::shared_ptr<app::ApplicationContext> ctx)
{
  return std::make_shared<SDL3Context>(ctx);
}

SDL_GLContext SDL3ContextBuilder::create_context(
    std::shared_ptr<SDL3Context> sdl3ctx)
{
  assert(sdl3ctx->window != nullptr);

  if (sdl3ctx->window == nullptr) {
    LOGE("No window object pointer provided");
    return nullptr;
  }

  return SDL_GL_CreateContext(sdl3ctx->window);
}

SDL_Window* SDL3ContextBuilder::create_window(
    [[maybe_unused]] std::shared_ptr<SDL3Context> sdl3ctx)
{
  return SDL_CreateWindow(get_window_title().c_str(), default_window_width,
                          default_window_height, get_create_window_flags());
}

const std::string& SDL3ContextBuilder::get_window_title()
{
  static const std::string windowTitle =
      project_decls::PROJECT_NAME + " " + project_decls::PROJECT_BUILD_VERSION;

  return windowTitle;
}

SDL_WindowFlags SDL3ContextBuilder::get_create_window_flags()
{
  return SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
}

}  // namespace templateSDL3
