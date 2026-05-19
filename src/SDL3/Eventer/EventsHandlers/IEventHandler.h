#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IEVENTHANDLER_ABSTRACT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IEVENTHANDLER_ABSTRACT_CLASS_H

#include <SDL3/SDL.h>

#include <memory>

#include "src/SDL3/SDL3Context.h"

namespace templateSDL3::events::eventsHandlers
{

/**
 * @brief An abstract class to define the interface for the each SDL3
 * event handle descendant.
 */
class IEventHandler
{
 public:
  virtual ~IEventHandler() = default;

  /**
   * @brief Call the specific descendant handle implementation for the event
   *
   * @param event The current event to handle.
   * @param ctx The SDL3 context to handle
   *
   * @return Returns a true boolean value on the success and a false otherwise.
   */
  virtual bool handle(SDL_Event& event,
                      std::shared_ptr<SDL3Context> sdl3Context) = 0;
};

}  // namespace templateSDL3::events::eventsHandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IEVENTHANDLER_ABSTRACT_CLASS_H
