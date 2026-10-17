#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FREEGLUTCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FREEGLUTCONTROLLER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace templateFreeGlut
{

/**
 * @brief Class to init and start the FreeGlut event loop.
 * Contains also the default display method to place
 * the OpenGL scene draw code.
 */
class FreeGlutController
{
 public:
  virtual ~FreeGlutController() = default;
  FreeGlutController() = default;

  /**
   * @brief Init and run the FreeGlut' OpenGL scene render pipeline until the
   * window is closed or a stop signal raises the context stop flag.
   *
   * @param ctx Application's run context with command line parameters etc.
   *
   * @return Returns the zero value on the success and the
   * IApplication::INVALID value without a valid context.
   */
  virtual int run(std::shared_ptr<app::ApplicationContext> ctx);

 protected:
  static void reshape(int w, int h);
  static void display();
  static void init();
  static void check_stop(int value);
};

}  // namespace templateFreeGlut

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FREEGLUTCONTROLLER_CLASS_H
