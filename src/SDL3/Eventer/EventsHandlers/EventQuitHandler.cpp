#include "src/SDL3/Eventer/EventsHandlers/EventQuitHandler.h"

#include <SDL3/SDL.h>

#include <cassert>
#include <memory>

namespace templateSDL3::events::eventsHandlers
{

bool EventQuitHandler::handle([[maybe_unused]] SDL_Event& event,
                              std::shared_ptr<SDL3Context> sdl3Context)
{
  assert(sdl3Context != nullptr);
  assert(sdl3Context->appCtx != nullptr);
  assert(event.type == SDL_EVENT_QUIT);

  if (sdl3Context == nullptr || sdl3Context->appCtx == nullptr) {
    return false;
  }

  sdl3Context->appCtx->stop(true);

  return true;
}

}  // namespace templateSDL3::events::eventsHandlers
