#include <memory>
#include <cassert>

#include <SDL2/SDL.h>

#include "src/SDL2/Eventer/EventsHandlers/EventQuitHandler.h"

namespace templateSDL2::events::eventsHandlers
{

bool EventQuitHandler::handle([[maybe_unused]] SDL_Event& event, std::shared_ptr<SDL2Context> sdl2Context)
{
  assert(sdl2Context != nullptr);
  assert(sdl2Context->appCtx != nullptr);
  assert(event.type == SDL_QUIT);

  if (sdl2Context == nullptr || sdl2Context->appCtx == nullptr) {
    return false;
  }

  sdl2Context->appCtx->stop(true);

  return true;
}

} // namespace templateSDL2::events::eventsHandlers
