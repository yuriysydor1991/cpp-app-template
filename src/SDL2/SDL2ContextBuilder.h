#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SDL2CONTEXTBUILDER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SDL2CONTEXTBUILDER_CLASS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <memory>

#include "src/SDL2/SDL2Context.h"
#include "src/app/ApplicationContext.h"

namespace templateSDL2
{

class SDL2ContextBuilder
{
 public:
  virtual ~SDL2ContextBuilder() = default;

  virtual std::shared_ptr<SDL2Context> build_context(
      std::shared_ptr<app::ApplicationContext> ctx);

 protected:
  virtual std::shared_ptr<SDL2Context> default_context(
      std::shared_ptr<app::ApplicationContext> ctx);
  virtual SDL_GLContext create_context(std::shared_ptr<SDL2Context> sdl2ctx);
  virtual SDL_Window* create_window(std::shared_ptr<SDL2Context> sdl2ctx);
  virtual SDL_WindowFlags get_create_window_flags();
  virtual const std::string& get_window_title();

  inline static constexpr const int default_window_width = 800;
  inline static constexpr const int default_window_height = 600;
};

}  // namespace templateSDL2

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SDL2CONTEXTBUILDER_CLASS_H
