#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTSHANDLERSFACTORY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTSHANDLERSFACTORY_CLASS_H

#include <memory>

#include <SDL2/SDL.h>

#include "src/SDL2/SDL2Context.h"
#include "src/SDL2/Eventer/EventsHandlers/IEventHandler.h"

namespace templateSDL2::events::eventsHandlers
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
   * @param ctx The SDL2 context to handle
   * 
   * @return Returns appropriate event handler object. Descendant of the IEventHandler.
   */
  virtual std::shared_ptr<IEventHandler> create(SDL_Event& event, std::shared_ptr<SDL2Context> sdl2Context);
};

} // namespace templateSDL2::events::eventsHandlers

#endif // YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTSHANDLERSFACTORY_CLASS_H
