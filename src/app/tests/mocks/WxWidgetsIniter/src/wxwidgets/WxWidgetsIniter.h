#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WXWIDGETSINITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WXWIDGETSINITER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace wxwi
{

class WxWidgetsIniter
{
 public:
  virtual ~WxWidgetsIniter() = default;
  WxWidgetsIniter()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(WxWidgetsIniter&)> onMockCreate;

  MOCK_METHOD(int, run, (std::shared_ptr<app::ApplicationContext>));
};

}  // namespace wxwi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WXWIDGETSINITER_CLASS_H
