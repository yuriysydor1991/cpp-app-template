#include "Painter.h"

#include <cassert>
#include <memory>

#include "src/SFML/sfml-includes.h"

namespace templateSFML::painter
{

bool Painter::paint(std::shared_ptr<SFMLContext> ctx)
{
  assert(ctx != nullptr);
  assert(ctx->window != nullptr);

  if (ctx == nullptr || ctx->window == nullptr) {
    return false;
  }

  ctx->window->clear(sf::Color::Black);

  // put your SFML 2D draw scene over here
  sf::CircleShape shape{100.F};
  shape.setFillColor(sf::Color::Green);
  shape.setPosition(300.F, 200.F);

  ctx->window->draw(shape);

  return true;
}

}  // namespace templateSFML::painter
