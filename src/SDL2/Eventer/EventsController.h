#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTSCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTSCONTROLLER_CLASS_H

#include <SDL2/SDL.h>

#include "src/SDL2/Eventer/EventsHandlers/EventsHandlersFactory.h"
#include "src/SDL2/SDL2Context.h"

/**
 * @brief The event handling subsystem namespace.
 */
namespace templateSDL2::events
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

  virtual bool handle(std::shared_ptr<SDL2Context> sdl2Context);

 private:
  SDL_Event event;
  std::shared_ptr<eventsHandlers::EventsHandlersFactory> factory;
};

}  // namespace templateSDL2::events

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTSCONTROLLER_CLASS_H
