#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SFML_EVENTSCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SFML_EVENTSCONTROLLER_CLASS_H

#include <memory>

#include "src/SFML/Eventer/EventsHandlers/EventsHandlersFactory.h"
#include "src/SFML/SFMLContext.h"

/**
 * @brief The event handling subsystem namespace.
 */
namespace templateSFML::events
{

/**
 * @brief An event subsystem controller. Polls the SFML window for the events
 * and dispatches them to the appropriate handlers.
 */
class EventsController
{
 public:
  virtual ~EventsController() = default;
  EventsController();

  virtual bool handle(std::shared_ptr<SFMLContext> sfmlContext);

 private:
  std::shared_ptr<eventsHandlers::EventsHandlersFactory> factory;
};

}  // namespace templateSFML::events

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SFML_EVENTSCONTROLLER_CLASS_H
