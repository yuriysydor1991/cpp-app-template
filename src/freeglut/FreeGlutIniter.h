#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FREEGLUT_OPENGL_INITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FREEGLUT_OPENGL_INITER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace templateFreeGlut
{

/**
 * @brief Class to init and start the FreeGlut event loop.
 * Contains also the default display method to place
 * the OpenGL scene draw code.
 */
class FreeGlutIniter
{
 public:
  virtual ~FreeGlutIniter() = default;
  FreeGlutIniter() = default;

  /**
   * @brief Init and run the FreeGlut' OpenGL scene render pipeline.
   *
   * @param ctx Application's run context with command line parameters etc.
   *
   * @return Returns the zero value on the success and other value otherwise.
   */
  virtual int run(std::shared_ptr<app::ApplicationContext> ctx);

 protected:
  static void reshape(int w, int h);
  static void display();
  static void init();
};

}  // namespace templateFreeGlut

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FREEGLUT_OPENGL_INITER_CLASS_H
