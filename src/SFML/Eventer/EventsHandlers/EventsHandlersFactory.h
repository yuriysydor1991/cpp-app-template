#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SFML_EVENTSHANDLERSFACTORY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SFML_EVENTSHANDLERSFACTORY_CLASS_H

#include <SFML/Window/Event.hpp>

#include <memory>

#include "src/SFML/Eventer/EventsHandlers/IEventHandler.h"
#include "src/SFML/SFMLContext.h"

namespace templateSFML::events::eventsHandlers
{

/**
 * @brief The factory for all the implemented events to handle.
 */
class EventsHandlersFactory
{
 public:
  virtual ~EventsHandlersFactory() = default;

  /**
   * @brief Creates appropriate event handler object to handle given event.
   *
   * @param event The current event to handle.
   * @param sfmlContext The SFML context to handle.
   *
   * @return Returns appropriate event handler object (descendant of the
   * IEventHandler) or a nullptr if the event is not handled.
   */
  virtual std::shared_ptr<IEventHandler> create(
      sf::Event& event, std::shared_ptr<SFMLContext> sfmlContext);
};

}  // namespace templateSFML::events::eventsHandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SFML_EVENTSHANDLERSFACTORY_CLASS_H
