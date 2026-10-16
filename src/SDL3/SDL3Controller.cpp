#include "src/SDL3/SDL3Controller.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <cassert>

#include "project-global-decls.h"
#include "src/app/applications/IApplication.h"
#include "src/log/log.h"

namespace templateSDL3
{

SDL3Controller::SDL3Controller()
    : ctxBuilder{std::make_shared<SDL3ContextBuilder>()},
      events{std::make_shared<events::EventsController>()},
      painter3d{std::make_shared<painter::Painter>()},
      oglIniter{std::make_shared<OpenGLIniter>()}
{
}

SDL3Controller::~SDL3Controller()
{
  sdl3Context.reset();

  SDL_Quit();
}

int SDL3Controller::run(std::shared_ptr<app::ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid application context provided");
    return app::IApplication::INVALID;
  }

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    LOGE(
        "Fail to init the SDL3 video subsystem, SDL_Error: " << SDL_GetError());
    return app::IApplication::INVALID;
  }

  if (!oglIniter->init_opengl()) {
    LOGE("Fail to initiate the OpenGL");
    return app::IApplication::INVALID;
  }

  sdl3Context = ctxBuilder->build_context(ctx);

  if (sdl3Context == nullptr) {
    LOGE("Fail to create the SDL3 context");
    return app::IApplication::INVALID;
  }

  event_loop();

  return 0;
}

void SDL3Controller::event_loop()
{
  assert(sdl3Context != nullptr);
  assert(events != nullptr);
  assert(painter3d != nullptr);

  // the window close and the stop signals handlers both raise the stop flag
  while (!sdl3Context->appCtx->get_stop()) {
    events->handle(sdl3Context);

    painter3d->paint(sdl3Context);

    SDL_GL_SwapWindow(sdl3Context->window);
  }
}

}  // namespace templateSDL3
