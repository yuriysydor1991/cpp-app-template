#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FREEGLUTCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FREEGLUTCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace templateFreeGlut
{

class FreeGlutController
{
 public:
  virtual ~FreeGlutController() = default;
  FreeGlutController()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(FreeGlutController&)> onMockCreate;

  MOCK_METHOD(int, run, (std::shared_ptr<app::ApplicationContext> ctx));
};

}  // namespace templateFreeGlut

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FREEGLUTCONTROLLER_CLASS_H
