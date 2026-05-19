#include "src/SDL3/Eventer/EventsHandlers/EventsHandlersFactory.h"

#include <SDL3/SDL.h>

#include <cassert>
#include <memory>

#include "src/SDL3/Eventer/EventsHandlers/EventQuitHandler.h"
#include "src/SDL3/Eventer/EventsHandlers/IEventHandler.h"
#include "src/SDL3/SDL3Context.h"

namespace templateSDL3::events::eventsHandlers
{

std::shared_ptr<IEventHandler> EventsHandlersFactory::create(
    SDL_Event& event, [[maybe_unused]] std::shared_ptr<SDL3Context> sdl3Context)
{
  assert(sdl3Context != nullptr);

  if (event.type == SDL_EVENT_QUIT) {
    return std::make_shared<EventQuitHandler>();
  }

  return {};
}

}  // namespace templateSDL3::events::eventsHandlers
