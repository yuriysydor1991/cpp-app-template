#include "src/SFML/Eventer/EventsHandlers/EventClosedHandler.h"

#include <SFML/Window/Event.hpp>

#include <cassert>
#include <memory>

namespace templateSFML::events::eventsHandlers
{

bool EventClosedHandler::handle([[maybe_unused]] sf::Event& event,
                                std::shared_ptr<SFMLContext> sfmlContext)
{
  assert(sfmlContext != nullptr);
  assert(sfmlContext->appCtx != nullptr);
  assert(event.type == sf::Event::Closed);

  if (sfmlContext == nullptr || sfmlContext->appCtx == nullptr) {
    return false;
  }

  sfmlContext->appCtx->stop(true);

  return true;
}

}  // namespace templateSFML::events::eventsHandlers
