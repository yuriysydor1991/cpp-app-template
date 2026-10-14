#include "src/app/applications/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/cocoa/CocoaController.h"
#include "src/log/log.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  std::shared_ptr<cocoa::CocoaController> controller =
      create_cocoa_controller();

  if (controller->run(ctx) != 0) {
    LOGE("The Cocoa controller returned invalid execution status");
    return INVALID;
  }

  return 0;
}

std::shared_ptr<cocoa::CocoaController> Application::create_cocoa_controller()
{
  return std::make_shared<cocoa::CocoaController>();
}

}  // namespace app
