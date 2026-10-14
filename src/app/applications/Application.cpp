#include "src/app/applications/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/log/log.h"
#include "src/qt6/Qt6Controller.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  std::shared_ptr<Qt6i::Qt6Controller> qt6runner = create_qt6_controller();

  assert(qt6runner != nullptr);

  if (qt6runner->run(ctx) != 0) {
    LOGE("Qt6 controller returned invalid status");
    return INVALID;
  }

  return 0;
}

std::shared_ptr<Qt6i::Qt6Controller> Application::create_qt6_controller()
{
  return std::make_shared<Qt6i::Qt6Controller>();
}

}  // namespace app
