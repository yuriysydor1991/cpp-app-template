#include "src/SDL2/SDL2Controller.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <cassert>

#include "project-global-decls.h"
#include "src/app/applications/IApplication.h"
#include "src/log/log.h"

namespace templateSDL2
{

SDL2Controller::SDL2Controller()
    : ctxBuilder{std::make_shared<SDL2ContextBuilder>()},
      events{std::make_shared<events::EventsController>()},
      painter3d{std::make_shared<painter::Painter>()},
      oglIniter{std::make_shared<OpenGLIniter>()}
{
}

SDL2Controller::~SDL2Controller()
{
  sdl2Context.reset();

  SDL_Quit();
}

int SDL2Controller::run(std::shared_ptr<app::ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid application context provided");
    return app::IApplication::INVALID;
  }

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    LOGE(
        "Fail to init the SDL2 video subsystem, SDL_Error: " << SDL_GetError());
    return app::IApplication::INVALID;
  }

  sdl2Context = ctxBuilder->build_context(ctx);

  if (sdl2Context == nullptr) {
    LOGE("Fail to create the SDL2 context");
    return app::IApplication::INVALID;
  }

  if (!oglIniter->init_opengl(sdl2Context)) {
    LOGE("Fail to initiate the OpenGL");
    return app::IApplication::INVALID;
  }

  event_loop();

  return 0;
}

void SDL2Controller::event_loop()
{
  assert(sdl2Context != nullptr);
  assert(events != nullptr);
  assert(painter3d != nullptr);

  // the window close and the stop signals handlers both raise the stop flag
  while (!sdl2Context->appCtx->get_stop()) {
    events->handle(sdl2Context);

    painter3d->paint(sdl2Context);

    SDL_GL_SwapWindow(sdl2Context->window);
  }
}

}  // namespace templateSDL2
