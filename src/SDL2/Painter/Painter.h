#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PAINTER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PAINTER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

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
   * @param ctx The Application run context with the parameters etc.
   *
   * @return Returns true on the success and false otherwise.
   */
  virtual bool paint(std::shared_ptr<app::ApplicationContext> ctx);
};

}  // namespace templateSDL2::painter

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PAINTER_CLASS_H
