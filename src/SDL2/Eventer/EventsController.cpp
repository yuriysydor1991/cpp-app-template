#include <memory>
#include <cassert>

#include <SDL2/SDL.h>

#include "src/SDL2/SDL2Context.h"
#include "src/SDL2/Eventer/EventsController.h"

namespace templateSDL2::events
{

EventsController::EventsController()
  : factory{std::make_shared<eventsHandlers::EventsHandlersFactory>()}
{}

bool EventsController::handle(std::shared_ptr<SDL2Context> sdl2Context)
{
  assert(sdl2Context != nullptr);
  assert(factory != nullptr);
  
  while (SDL_PollEvent(&event)) {
    std::shared_ptr<eventsHandlers::IEventHandler> handler = factory->create(event, sdl2Context);

    if (handler == nullptr) {
      continue;
    }

    handler->handle(event, sdl2Context);
  }

  return true;
}

} // namespace templateSDL2::events