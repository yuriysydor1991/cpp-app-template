#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTWINDOWRESIZEDHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTWINDOWRESIZEDHANDLER_CLASS_H

#include <SDL3/SDL.h>

#include <memory>

#include "src/SDL3/Eventer/EventsHandlers/IEventHandler.h"

namespace templateSDL3::events::eventsHandlers
{

/**
 * @brief The window pixel size change handler class. Keeps the OpenGL
 * viewport covering the whole resized window.
 */
class EventWindowResizedHandler : public IEventHandler
{
 public:
  ~EventWindowResizedHandler() override = default;

  /**
   * @brief Sets the OpenGL viewport to the new window size in pixels.
   */
  bool handle(SDL_Event& event,
              std::shared_ptr<SDL3Context> sdl3Context) override;
};

}  // namespace templateSDL3::events::eventsHandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_EVENTWINDOWRESIZEDHANDLER_CLASS_H
