#include <memory>
#include <cassert>

#include <SDL2/SDL.h>

#include "src/SDL2/Eventer/EventsHandlers/EventsHandlersFactory.h"
#include "src/SDL2/SDL2Context.h"
#include "src/SDL2/Eventer/EventsHandlers/IEventHandler.h"
#include "src/SDL2/Eventer/EventsHandlers/EventQuitHandler.h"

namespace templateSDL2::events::eventsHandlers
{

std::shared_ptr<IEventHandler> EventsHandlersFactory::create(SDL_Event& event, [[maybe_unused]] std::shared_ptr<SDL2Context> sdl2Context)
{
  assert(sdl2Context != nullptr);

  if (event.type == SDL_QUIT) {
    return std::make_shared<EventQuitHandler>();
  }

  return {};
}

} // namespace templateSDL2::events::eventsHandlers
