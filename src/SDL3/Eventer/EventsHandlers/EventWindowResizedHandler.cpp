#include "src/SDL3/Eventer/EventsHandlers/EventWindowResizedHandler.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <cassert>
#include <memory>

namespace templateSDL3::events::eventsHandlers
{

bool EventWindowResizedHandler::handle(
    SDL_Event& event, [[maybe_unused]] std::shared_ptr<SDL3Context> sdl3Context)
{
  assert(event.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED);

  glViewport(0, 0, event.window.data1, event.window.data2);

  return true;
}

}  // namespace templateSDL3::events::eventsHandlers
