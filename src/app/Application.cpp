#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/log/log.h"
#include "src/winui3/WinUI3Initer.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  std::shared_ptr<winui3::WinUI3Initer> initer = create_winui3_initer();

  if (initer->run(ctx) != 0) {
    LOGE("The WinUI 3 controller returned invalid execution status");
    return INVALID;
  }

  return 0;
}

std::shared_ptr<winui3::WinUI3Initer> Application::create_winui3_initer()
{
  return std::make_shared<winui3::WinUI3Initer>();
}

}  // namespace app
