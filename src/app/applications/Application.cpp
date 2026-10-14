#include "src/app/applications/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/log/log.h"
#include "src/wxwidgets/WxWidgetsController.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  std::shared_ptr<wxwi::WxWidgetsController> wxController =
      create_wx_controller();

  if (wxController->run(ctx) != 0) {
    LOGE("The wxWidgets controller returned invalid execution status");
    return INVALID;
  }

  return 0;
}

std::shared_ptr<wxwi::WxWidgetsController> Application::create_wx_controller()
{
  return std::make_shared<wxwi::WxWidgetsController>();
}

}  // namespace app
