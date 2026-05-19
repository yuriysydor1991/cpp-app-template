#include "src/SDL3/Eventer/EventsController.h"

#include <SDL3/SDL.h>

#include <cassert>
#include <memory>

#include "src/SDL3/SDL3Context.h"

namespace templateSDL3::events
{

EventsController::EventsController()
    : factory{std::make_shared<eventsHandlers::EventsHandlersFactory>()}
{
}

bool EventsController::handle(std::shared_ptr<SDL3Context> sdl3Context)
{
  assert(sdl3Context != nullptr);
  assert(factory != nullptr);

  while (SDL_PollEvent(&event)) {
    std::shared_ptr<eventsHandlers::IEventHandler> handler =
        factory->create(event, sdl3Context);

    if (handler == nullptr) {
      continue;
    }

    handler->handle(event, sdl3Context);
  }

  return true;
}

}  // namespace templateSDL3::events
