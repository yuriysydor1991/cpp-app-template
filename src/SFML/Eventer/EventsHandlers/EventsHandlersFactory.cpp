#include "src/SFML/Eventer/EventsHandlers/EventsHandlersFactory.h"

#include <SFML/Window/Event.hpp>

#include <cassert>
#include <memory>

#include "src/SFML/Eventer/EventsHandlers/EventClosedHandler.h"
#include "src/SFML/Eventer/EventsHandlers/IEventHandler.h"
#include "src/SFML/SFMLContext.h"

namespace templateSFML::events::eventsHandlers
{

std::shared_ptr<IEventHandler> EventsHandlersFactory::create(
    sf::Event& event, [[maybe_unused]] std::shared_ptr<SFMLContext> sfmlContext)
{
  assert(sfmlContext != nullptr);

  if (event.type == sf::Event::Closed) {
    return std::make_shared<EventClosedHandler>();
  }

  return {};
}

}  // namespace templateSFML::events::eventsHandlers
