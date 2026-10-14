#include "src/app/applications/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/log/log.h"
#include "src/winui3/WinUI3Controller.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  std::shared_ptr<winui3::WinUI3Controller> controller =
      create_winui3_controller();

  if (controller->run(ctx) != 0) {
    LOGE("The WinUI 3 controller returned invalid execution status");
    return INVALID;
  }

  return 0;
}

std::shared_ptr<winui3::WinUI3Controller>
Application::create_winui3_controller()
{
  return std::make_shared<winui3::WinUI3Controller>();
}

}  // namespace app
