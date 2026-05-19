#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTSCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTSCONTROLLER_CLASS_H

#include <SDL3/SDL.h>

#include "src/SDL3/Eventer/EventsHandlers/EventsHandlersFactory.h"
#include "src/SDL3/SDL3Context.h"

/**
 * @brief The event handling subsystem namespace.
 */
namespace templateSDL3::events
{

/**
 * @brief An event subsystem controller. Checks for the events
 * and tries to parse them.
 */
class EventsController
{
 public:
  virtual ~EventsController() = default;
  EventsController();

  virtual bool handle(std::shared_ptr<SDL3Context> sdl3Context);

 private:
  SDL_Event event;
  std::shared_ptr<eventsHandlers::EventsHandlersFactory> factory;
};

}  // namespace templateSDL3::events

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTSCONTROLLER_CLASS_H
