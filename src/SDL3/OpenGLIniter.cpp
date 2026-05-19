#include "src/SDL3/OpenGLIniter.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <memory>

#include "src/SDL3/SDL3Context.h"
#include "src/log/log.h"

namespace templateSDL3
{

bool OpenGLIniter::init_opengl(
    [[maybe_unused]] std::shared_ptr<SDL3Context> sd3Context)
{
  if (!set_opengl_attributes()) {
    LOGE("Failure to set the OpenGL attributes");
    return false;
  }

  return true;
}

bool OpenGLIniter::set_opengl_attributes()
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_CONTEXT_MAJOR_VERSION);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_CONTEXT_MINOR_VERSION);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  return true;
}

}  // namespace templateSDL3
