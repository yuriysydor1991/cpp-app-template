#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IEVENTHANDLER_ABSTRACT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IEVENTHANDLER_ABSTRACT_CLASS_H

#include <SDL2/SDL.h>

#include <memory>

#include "src/SDL2/SDL2Context.h"

namespace templateSDL2::events::eventsHandlers
{

/**
 * @brief An abstract class to define the interface for the each SDL2
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
   * @param ctx The SDL2 context to handle
   *
   * @return Returns a true boolean value on the success and a false otherwise.
   */
  virtual bool handle(SDL_Event& event,
                      std::shared_ptr<SDL2Context> sdl2Context) = 0;
};

}  // namespace templateSDL2::events::eventsHandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IEVENTHANDLER_ABSTRACT_CLASS_H
