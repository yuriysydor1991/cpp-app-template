#include "src/SDL2/Eventer/EventsHandlers/EventWindowResizedHandler.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <cassert>
#include <memory>

namespace templateSDL2::events::eventsHandlers
{

bool EventWindowResizedHandler::handle(
    SDL_Event& event, [[maybe_unused]] std::shared_ptr<SDL2Context> sdl2Context)
{
  assert(event.type == SDL_WINDOWEVENT &&
         event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED);

  glViewport(0, 0, event.window.data1, event.window.data2);

  return true;
}

}  // namespace templateSDL2::events::eventsHandlers
