#include "src/SDL3/OpenGLIniter.h"

#include <SDL3/SDL.h>

#include "src/log/log.h"

namespace templateSDL3
{

bool OpenGLIniter::init_opengl()
{
  if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,
                           GL_CONTEXT_MAJOR_VERSION) ||
      !SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,
                           GL_CONTEXT_MINOR_VERSION) ||
      !SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                           SDL_GL_CONTEXT_PROFILE_CORE)) {
    LOGE("Failure to set the OpenGL attributes, SDL_Error: " << SDL_GetError());
    return false;
  }

  return true;
}

}  // namespace templateSDL3
