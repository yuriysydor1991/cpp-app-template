#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SFML_IEVENTHANDLER_ABSTRACT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SFML_IEVENTHANDLER_ABSTRACT_CLASS_H

#include <SFML/Window/Event.hpp>

#include <memory>

#include "src/SFML/SFMLContext.h"

namespace templateSFML::events::eventsHandlers
{

/**
 * @brief An abstract class to define the interface for the each SFML
 * event handle descendant.
 */
class IEventHandler
{
 public:
  virtual ~IEventHandler() = default;

  /**
   * @brief Call the specific descendant handle implementation for the event.
   *
   * @param event The current event to handle.
   * @param sfmlContext The SFML context to handle.
   *
   * @return Returns a true boolean value on the success and a false otherwise.
   */
  virtual bool handle(sf::Event& event,
                      std::shared_ptr<SFMLContext> sfmlContext) = 0;
};

}  // namespace templateSFML::events::eventsHandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SFML_IEVENTHANDLER_ABSTRACT_CLASS_H
