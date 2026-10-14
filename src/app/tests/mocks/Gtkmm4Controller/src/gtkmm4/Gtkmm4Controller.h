#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4CONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4CONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace Gtkmm4i
{

class Gtkmm4Controller
{
 public:
  virtual ~Gtkmm4Controller() = default;
  Gtkmm4Controller()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(Gtkmm4Controller&)> onMockCreate;

  MOCK_METHOD(int, run, (std::shared_ptr<app::ApplicationContext>));
};

}  // namespace Gtkmm4i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4CONTROLLER_CLASS_H
