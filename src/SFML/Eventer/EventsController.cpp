#include "src/SFML/Eventer/EventsController.h"

#include <cassert>
#include <memory>

#include "src/SFML/SFMLContext.h"
#include "src/SFML/sfml-includes.h"

namespace templateSFML::events
{

EventsController::EventsController()
    : factory{std::make_shared<eventsHandlers::EventsHandlersFactory>()}
{
}

bool EventsController::handle(std::shared_ptr<SFMLContext> sfmlContext)
{
  assert(sfmlContext != nullptr);
  assert(sfmlContext->window != nullptr);
  assert(factory != nullptr);

  sf::Event event;

  while (sfmlContext->window->pollEvent(event)) {
    std::shared_ptr<eventsHandlers::IEventHandler> handler =
        factory->create(event, sfmlContext);

    if (handler == nullptr) {
      continue;
    }

    handler->handle(event, sfmlContext);
  }

  return true;
}

}  // namespace templateSFML::events
