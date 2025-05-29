#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SDL2INITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SDL2INITER_CLASS_H

#include <memory>

#include "src/SDL2/Eventer/EventsController.h"
#include "src/SDL2/OpenGLIniter.h"
#include "src/SDL2/Painter/Painter.h"
#include "src/SDL2/SDL2Context.h"
#include "src/SDL2/SDL2ContextBuilder.h"
#include "src/app/ApplicationContext.h"

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
  static void throw_sdl2(const std::string& errDesc);
  virtual void event_loop();

  std::shared_ptr<SDL2ContextBuilder> ctxBuilder;
  std::shared_ptr<SDL2Context> sdl2Context;

  std::shared_ptr<events::EventsController> events;
  std::shared_ptr<painter::Painter> painter3d;
  std::shared_ptr<OpenGLIniter> oglIniter;
};

}  // namespace templateSDL2

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SDL2INITER_CLASS_H
