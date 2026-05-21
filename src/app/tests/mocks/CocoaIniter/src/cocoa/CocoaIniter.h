#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_COCOAINITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_COCOAINITER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace cocoa
{

class CocoaIniter
{
 public:
  virtual ~CocoaIniter() = default;
  CocoaIniter()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(CocoaIniter&)> onMockCreate;

  MOCK_METHOD(int, run, (std::shared_ptr<app::ApplicationContext>));
};

}  // namespace cocoa

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_COCOAINITER_CLASS_H
