#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SFML_PAINTER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SFML_PAINTER_CLASS_H

#include <memory>

#include "src/SFML/SFMLContext.h"

namespace templateSFML::painter
{

/**
 * @brief The 2D scene draw class.
 */
class Painter
{
 public:
  virtual ~Painter() = default;
  Painter() = default;

  /**
   * @brief paint Single draw of the 2D scene onto the render window.
   *
   * @param ctx The SFML run context with the render window etc.
   *
   * @return Returns true on the success and false otherwise.
   */
  virtual bool paint(std::shared_ptr<SFMLContext> ctx);
};

}  // namespace templateSFML::painter

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SFML_PAINTER_CLASS_H
