#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGLINITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGLINITER_CLASS_H

#include <memory>

#include "src/SDL3/SDL3Context.h"

namespace templateSDL3
{

class OpenGLIniter
{
 public:
  virtual ~OpenGLIniter() = default;

  virtual bool init_opengl(std::shared_ptr<SDL3Context> sd3Context);

 private:
  virtual bool set_opengl_attributes();

  inline static constexpr const int GL_CONTEXT_MAJOR_VERSION = 3;
  inline static constexpr const int GL_CONTEXT_MINOR_VERSION = 3;
};

}  // namespace templateSDL3

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OPENGLINITER_CLASS_H
