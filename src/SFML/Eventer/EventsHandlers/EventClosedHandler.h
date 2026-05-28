#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SFML_EVENTCLOSEDHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SFML_EVENTCLOSEDHANDLER_CLASS_H

#include <SFML/Window/Event.hpp>

#include <memory>

#include "src/SFML/Eventer/EventsHandlers/IEventHandler.h"
#include "src/app/ApplicationContext.h"

namespace templateSFML::events::eventsHandlers
{

/**
 * @brief The window closed event handler class. Requests the application to
 * stop its SFML event loop.
 */
class EventClosedHandler : public IEventHandler
{
 public:
  virtual ~EventClosedHandler() = default;

  /**
   * @brief The closed event handler routine.
   */
  virtual bool handle(sf::Event& event,
                      std::shared_ptr<SFMLContext> sfmlContext) override;
};

}  // namespace templateSFML::events::eventsHandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SFML_EVENTCLOSEDHANDLER_CLASS_H
