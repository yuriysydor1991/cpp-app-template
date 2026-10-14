#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WXWIDGETSCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WXWIDGETSCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace wxwi
{

class WxWidgetsController
{
 public:
  virtual ~WxWidgetsController() = default;
  WxWidgetsController()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(WxWidgetsController&)> onMockCreate;

  MOCK_METHOD(int, run, (std::shared_ptr<app::ApplicationContext>));
};

}  // namespace wxwi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WXWIDGETSCONTROLLER_CLASS_H
