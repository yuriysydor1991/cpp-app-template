#include "Painter.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <cassert>
#include <memory>

namespace templateSDL3::painter
{

bool Painter::paint([[maybe_unused]] std::shared_ptr<SDL3Context> ctx)
{
  glClear(GL_COLOR_BUFFER_BIT);

  // put the OpenGL draw scene over here

  return true;
}

}  // namespace templateSDL3::painter
