#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/cocoa/CocoaIniter.h"
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

  std::shared_ptr<cocoa::CocoaIniter> initer = create_cocoa_initer();

  if (initer->run(ctx) != 0) {
    LOGE("The Cocoa controller returned invalid execution status");
    return INVALID;
  }

  return 0;
}

std::shared_ptr<cocoa::CocoaIniter> Application::create_cocoa_initer()
{
  return std::make_shared<cocoa::CocoaIniter>();
}

}  // namespace app
