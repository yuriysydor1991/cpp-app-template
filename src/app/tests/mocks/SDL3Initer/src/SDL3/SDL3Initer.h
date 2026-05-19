#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SDL3INITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SDL3INITER_CLASS_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace templateSDL3
{

class SDL3Initer
{
 public:
  virtual ~SDL3Initer() = default;
  SDL3Initer()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(SDL3Initer& instance)> onMockCreate;

  MOCK_METHOD(int, run, (std::shared_ptr<app::ApplicationContext> ctx));
};

}  // namespace templateSDL3

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SDL3INITER_CLASS_H
