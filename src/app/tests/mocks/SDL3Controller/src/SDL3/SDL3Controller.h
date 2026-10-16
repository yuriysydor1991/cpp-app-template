#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SDL3CONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SDL3CONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace templateSDL3
{

class SDL3Controller
{
 public:
  virtual ~SDL3Controller() = default;
  SDL3Controller()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(SDL3Controller& instance)> onMockCreate;

  MOCK_METHOD(int, run, (std::shared_ptr<app::ApplicationContext> ctx));
};

}  // namespace templateSDL3

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SDL3CONTROLLER_CLASS_H
