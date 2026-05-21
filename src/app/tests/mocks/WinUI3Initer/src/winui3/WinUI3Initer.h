#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3INITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3INITER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace winui3
{

class WinUI3Initer
{
 public:
  virtual ~WinUI3Initer() = default;
  WinUI3Initer()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(WinUI3Initer&)> onMockCreate;

  MOCK_METHOD(int, run, (std::shared_ptr<app::ApplicationContext>));
};

}  // namespace winui3

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3INITER_CLASS_H
