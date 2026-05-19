#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTQUITHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTQUITHANDLER_CLASS_H

#include <SDL3/SDL.h>

#include <memory>

#include "src/SDL3/Eventer/EventsHandlers/IEventHandler.h"
#include "src/app/ApplicationContext.h"

namespace templateSDL3::events::eventsHandlers
{

/**
 * @brief The quit event handler class
 */
class EventQuitHandler : public IEventHandler
{
 public:
  virtual ~EventQuitHandler() = default;

  /**
   * @brief The quit event handler routine
   */
  virtual bool handle(SDL_Event& event,
                      std::shared_ptr<SDL3Context> sdl3Context) override;
};

}  // namespace templateSDL3::events::eventsHandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTQUITHANDLER_CLASS_H
