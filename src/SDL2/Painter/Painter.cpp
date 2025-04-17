#include "Painter.h"

#include <cassert>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace templateSDL2::painter
{

bool Painter::paint([[maybe_unused]] std::shared_ptr<app::ApplicationContext> ctx)
{
  glClear(GL_COLOR_BUFFER_BIT);

  // put the OpenGL draw scene over here

  return true;
}

}  // namespace templateSDL2::painter
