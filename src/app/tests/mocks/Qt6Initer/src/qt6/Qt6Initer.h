#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_QT6INITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_QT6INITER_CLASS_H

#include <gmock/gmock.h>

#include <memory>

#include "src/app/ApplicationContext.h"

namespace Qt6i
{

class Qt6Initer
{
 public:
  virtual ~Qt6Initer() = default;
  Qt6Initer()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(Qt6Initer& instance)> onMockCreate;

  MOCK_METHOD(int, run, (std::shared_ptr<app::ApplicationContext>));
};

}  // namespace Qt6i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_QT6INITER_CLASS_H
