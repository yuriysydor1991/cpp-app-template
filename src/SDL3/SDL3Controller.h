#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SDL3CONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SDL3CONTROLLER_CLASS_H

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
class SDL3Controller
{
 public:
  virtual ~SDL3Controller();
  SDL3Controller();

  /**
   * @brief Init and run the SDL3 event loop until the window is closed or
   * a stop signal raises the context stop flag.
   *
   * @param ctx Application's run context with command line parameters etc.
   *
   * @return Returns the init and run return status. A zero value on the success
   * and the IApplication::INVALID value if the SDL3 video subsystem, the window
   * or the OpenGL context can't be created (e.g. no display available).
   */
  virtual int run(std::shared_ptr<app::ApplicationContext> ctx);

 protected:
  virtual void event_loop();

  std::shared_ptr<SDL3ContextBuilder> ctxBuilder;
  std::shared_ptr<SDL3Context> sdl3Context;

  std::shared_ptr<events::EventsController> events;
  std::shared_ptr<painter::Painter> painter3d;
  std::shared_ptr<OpenGLIniter> oglIniter;
};

}  // namespace templateSDL3

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SDL3CONTROLLER_CLASS_H
