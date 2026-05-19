#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTSHANDLERSFACTORY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTSHANDLERSFACTORY_CLASS_H

#include <SDL3/SDL.h>

#include <memory>

#include "src/SDL3/Eventer/EventsHandlers/IEventHandler.h"
#include "src/SDL3/SDL3Context.h"

namespace templateSDL3::events::eventsHandlers
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
   * @param ctx The SDL3 context to handle
   *
   * @return Returns appropriate event handler object. Descendant of the
   * IEventHandler.
   */
  virtual std::shared_ptr<IEventHandler> create(
      SDL_Event& event, std::shared_ptr<SDL3Context> sdl3Context);
};

}  // namespace templateSDL3::events::eventsHandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTSHANDLERSFACTORY_CLASS_H
