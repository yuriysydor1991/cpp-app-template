#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PAINTER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PAINTER_CLASS_H

#include <memory>

#include "src/SDL2/SDL2Context.h"

namespace templateSDL2::painter
{

/**
 * @brief The 3D scene draw class.
 */
class Painter
{
 public:
  virtual ~Painter() = default;
  Painter() = default;

  /**
   * @brief paint Single draw the 3D scene.
   *
   * @param ctx The SDL2 run context with the parameters etc.
   *
   * @return Returns true on the success and false otherwise.
   */
  virtual bool paint(std::shared_ptr<SDL2Context> ctx);
};

}  // namespace templateSDL2::painter

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PAINTER_CLASS_H
