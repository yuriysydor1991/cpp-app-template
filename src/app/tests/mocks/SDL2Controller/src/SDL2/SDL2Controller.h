#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SDL2CONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SDL2CONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace templateSDL2
{

class SDL2Controller
{
 public:
  virtual ~SDL2Controller() = default;
  SDL2Controller()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(SDL2Controller& instance)> onMockCreate;

  MOCK_METHOD(int, run, (std::shared_ptr<app::ApplicationContext> ctx));
};

}  // namespace templateSDL2

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SDL2CONTROLLER_CLASS_H
