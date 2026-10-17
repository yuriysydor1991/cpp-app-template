#include "src/SDL2/OpenGLIniter.h"

#include <SDL2/SDL.h>

#include "src/log/log.h"

namespace templateSDL2
{

bool OpenGLIniter::init_opengl()
{
  if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,
                          GL_CONTEXT_MAJOR_VERSION) != 0 ||
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,
                          GL_CONTEXT_MINOR_VERSION) != 0 ||
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                          SDL_GL_CONTEXT_PROFILE_CORE) != 0) {
    LOGE("Failure to set the OpenGL attributes, SDL_Error: " << SDL_GetError());
    return false;
  }

  return true;
}

}  // namespace templateSDL2
