#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTQUITHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTQUITHANDLER_CLASS_H

#include <memory>

#include <SDL2/SDL.h>

#include "src/app/ApplicationContext.h"
#include "src/SDL2/Eventer/EventsHandlers/IEventHandler.h"

namespace templateSDL2::events::eventsHandlers
{

/**
 * @brief The quit event handler class
 */
class EventQuitHandler: public IEventHandler
{
public:
  virtual ~EventQuitHandler() = default;

  /**
   * @brief The quit event handler routine
   */
  virtual bool handle(SDL_Event& event, std::shared_ptr<SDL2Context> sdl2Context) override;
};

} // namespace templateSDL2::events::eventsHandlers

#endif // YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTQUITHANDLER_CLASS_H
