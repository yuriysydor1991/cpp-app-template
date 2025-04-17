#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SDL2INITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SDL2INITER_CLASS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/SDL2/Painter/Painter.h"

namespace templateSDL2
{

/**
 * @brief The initialization and event loop runner class for the SDL2.
 */
class SDL2Initer
{
 public:
  virtual ~SDL2Initer();
  SDL2Initer();

  /**
   * @brief Init and run the SDL2 event loop.
   *
   * @param ctx Application's run context with command line parameters etc.
   *
   * @return Returns the init and run return status. A zero value on the success
   * and other value otherwise.
   */
  virtual int run(std::shared_ptr<app::ApplicationContext> ctx);

 protected:
  virtual void throw_sdl2(const std::string& errDesc);
  virtual bool init_opengl();
  virtual SDL_WindowFlags get_create_window_flags();
  virtual const std::string& get_window_title();
  virtual SDL_Window* create_window();
  virtual bool set_opengl_attributes();
  virtual SDL_GLContext create_context();
  virtual void eventer();
  virtual void parse_event(SDL_Event& event);
  virtual void event_loop();

  virtual void handleQuit(SDL_Event& event);

  inline static constexpr const int GL_CONTEXT_MAJOR_VERSION = 3;
  inline static constexpr const int GL_CONTEXT_MINOR_VERSION = 3;
  inline static constexpr const int default_window_width = 800;
  inline static constexpr const int default_window_height = 600;

  std::shared_ptr<app::ApplicationContext> mAppCtx;
  SDL_Window* window{nullptr};
  SDL_GLContext glContext{nullptr};

  std::shared_ptr<painter::Painter> painter3d;
};

}  // namespace templateSDL2

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SDL2INITER_CLASS_H
