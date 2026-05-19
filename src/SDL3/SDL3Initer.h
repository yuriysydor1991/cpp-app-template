#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SDL3INITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SDL3INITER_CLASS_H

#include <memory>

#include "src/SDL3/Eventer/EventsController.h"
#include "src/SDL3/OpenGLIniter.h"
#include "src/SDL3/Painter/Painter.h"
#include "src/SDL3/SDL3Context.h"
#include "src/SDL3/SDL3ContextBuilder.h"
#include "src/app/ApplicationContext.h"

namespace templateSDL3
{

/**
 * @brief The initialization and event loop runner class for the SDL3.
 */
class SDL3Initer
{
 public:
  virtual ~SDL3Initer();
  SDL3Initer();

  /**
   * @brief Init and run the SDL3 event loop.
   *
   * @param ctx Application's run context with command line parameters etc.
   *
   * @return Returns the init and run return status. A zero value on the success
   * and other value otherwise.
   */
  virtual int run(std::shared_ptr<app::ApplicationContext> ctx);

 protected:
  static void throw_sdl3(const std::string& errDesc);
  virtual void event_loop();

  std::shared_ptr<SDL3ContextBuilder> ctxBuilder;
  std::shared_ptr<SDL3Context> sdl3Context;

  std::shared_ptr<events::EventsController> events;
  std::shared_ptr<painter::Painter> painter3d;
  std::shared_ptr<OpenGLIniter> oglIniter;
};

}  // namespace templateSDL3

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SDL3INITER_CLASS_H
