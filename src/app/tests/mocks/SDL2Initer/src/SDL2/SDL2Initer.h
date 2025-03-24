#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SDL2INITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SDL2INITER_CLASS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <memory>
#include <functional>

#include <gmock/gmock.h>

#include "src/app/ApplicationContext.h"

namespace templateSDL2
{

class SDL2Initer
{
 public:
  virtual ~SDL2Initer() = default;
  SDL2Initer() 
  {
    if (onMockCreate) { onMockCreate(*this); }
  }

  inline static std::function<void(SDL2Initer& instance)> onMockCreate;

  MOCK_METHOD(int, run, (std::shared_ptr<app::ApplicationContext> ctx));
};

}  // namespace templateSDL2

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SDL2INITER_CLASS_H
