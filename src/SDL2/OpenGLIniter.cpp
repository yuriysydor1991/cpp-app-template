#include "src/SDL2/OpenGLIniter.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <memory>

#include "src/SDL2/SDL2Context.h"

namespace templateSDL2
{

bool OpenGLIniter::init_opengl(
    [[maybe_unused]] std::shared_ptr<SDL2Context> sd2Context)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    return false;
  }

  if (!set_opengl_attributes()) {
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

}  // namespace templateSDL2
