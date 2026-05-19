#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SDL3CONTEXTBUILDER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SDL3CONTEXTBUILDER_CLASS_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <memory>

#include "src/SDL3/SDL3Context.h"
#include "src/app/ApplicationContext.h"

namespace templateSDL3
{

class SDL3ContextBuilder
{
 public:
  virtual ~SDL3ContextBuilder() = default;

  virtual std::shared_ptr<SDL3Context> build_context(
      std::shared_ptr<app::ApplicationContext> ctx);

 protected:
  virtual std::shared_ptr<SDL3Context> default_context(
      std::shared_ptr<app::ApplicationContext> ctx);
  virtual SDL_GLContext create_context(std::shared_ptr<SDL3Context> sdl3ctx);
  virtual SDL_Window* create_window(std::shared_ptr<SDL3Context> sdl3ctx);
  virtual SDL_WindowFlags get_create_window_flags();
  virtual const std::string& get_window_title();

  inline static constexpr const int default_window_width = 800;
  inline static constexpr const int default_window_height = 600;
};

}  // namespace templateSDL3

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SDL3CONTEXTBUILDER_CLASS_H
