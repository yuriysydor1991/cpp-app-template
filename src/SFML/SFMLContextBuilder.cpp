#include "src/SFML/SFMLContextBuilder.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include <cassert>
#include <memory>

#include "project-global-decls.h"
#include "src/SFML/SFMLContext.h"
#include "src/app/ApplicationContext.h"
#include "src/log/log.h"

namespace templateSFML
{

std::shared_ptr<SFMLContext> SFMLContextBuilder::build_context(
    std::shared_ptr<app::ApplicationContext> ctx)
{
  std::shared_ptr<SFMLContext> sfmlctx = default_context(ctx);

  sfmlctx->window = create_window(sfmlctx);

  if (sfmlctx->window == nullptr) {
    LOGE("No window object pointer provided");
    return {};
  }

  return sfmlctx;
}

std::shared_ptr<SFMLContext> SFMLContextBuilder::default_context(
    std::shared_ptr<app::ApplicationContext> ctx)
{
  return std::make_shared<SFMLContext>(ctx);
}

std::unique_ptr<sf::RenderWindow> SFMLContextBuilder::create_window(
    [[maybe_unused]] std::shared_ptr<SFMLContext> sfmlctx)
{
  return std::make_unique<sf::RenderWindow>(
      sf::VideoMode(default_window_width, default_window_height),
      get_window_title(), sf::Style::Default);
}

const std::string& SFMLContextBuilder::get_window_title()
{
  static const std::string windowTitle =
      project_decls::PROJECT_NAME + " " + project_decls::PROJECT_BUILD_VERSION;

  return windowTitle;
}

}  // namespace templateSFML
