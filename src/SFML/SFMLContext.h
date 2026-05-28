#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SFMLCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SFMLCONTEXT_CLASS_H

#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>

#include "src/app/ApplicationContext.h"

namespace templateSFML
{

/**
 * @brief Aggregates the SFML render window together with the owning
 * application context, so the whole component can be driven through a single
 * shared object.
 */
struct SFMLContext
{
  virtual ~SFMLContext();
  explicit SFMLContext(std::shared_ptr<app::ApplicationContext> ctx);

  std::shared_ptr<app::ApplicationContext> appCtx;

  /// @brief The SFML render window. Stays nullptr until the context builder
  /// opens it, which keeps the headless test builds away from a real display.
  std::unique_ptr<sf::RenderWindow> window;
};

}  // namespace templateSFML

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SFMLCONTEXT_CLASS_H
