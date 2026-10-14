#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM3CONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM3CONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace Gtkmm3i
{

class Gtkmm3Controller
{
 public:
  virtual ~Gtkmm3Controller() = default;
  Gtkmm3Controller()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(Gtkmm3Controller&)> onMockCreate;

  MOCK_METHOD(int, run, (std::shared_ptr<app::ApplicationContext>));
};

}  // namespace Gtkmm3i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM3CONTROLLER_CLASS_H
