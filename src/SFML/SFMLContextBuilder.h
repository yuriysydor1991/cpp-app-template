#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SFMLCONTEXTBUILDER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SFMLCONTEXTBUILDER_CLASS_H

#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>
#include <string>

#include "src/SFML/SFMLContext.h"
#include "src/app/ApplicationContext.h"

namespace templateSFML
{

/**
 * @brief Builds a ready to use SFMLContext (with an opened render window) out
 * of the application context.
 */
class SFMLContextBuilder
{
 public:
  virtual ~SFMLContextBuilder() = default;

  virtual std::shared_ptr<SFMLContext> build_context(
      std::shared_ptr<app::ApplicationContext> ctx);

 protected:
  virtual std::shared_ptr<SFMLContext> default_context(
      std::shared_ptr<app::ApplicationContext> ctx);
  virtual std::unique_ptr<sf::RenderWindow> create_window(
      std::shared_ptr<SFMLContext> sfmlctx);
  virtual const std::string& get_window_title();

  inline static constexpr const unsigned int default_window_width = 800;
  inline static constexpr const unsigned int default_window_height = 600;
};

}  // namespace templateSFML

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SFMLCONTEXTBUILDER_CLASS_H
