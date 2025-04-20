#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGLINITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGLINITER_CLASS_H

#include <memory>

#include "src/SDL2/SDL2Context.h"

namespace templateSDL2
{

class OpenGLIniter
{
 public:
  virtual ~OpenGLIniter() = default;

  virtual bool init_opengl(std::shared_ptr<SDL2Context> sd2Context);

 private:
  virtual bool set_opengl_attributes();

  inline static constexpr const int GL_CONTEXT_MAJOR_VERSION = 3;
  inline static constexpr const int GL_CONTEXT_MINOR_VERSION = 3;
};

}  // namespace templateSDL2

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGLINITER_CLASS_H
