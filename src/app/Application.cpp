#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/log/log.h"
#include "src/wxwidgets/WxWidgetsIniter.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  std::shared_ptr<wxwi::WxWidgetsIniter> wxIniter = create_wx_initer();

  if (wxIniter->run(ctx) != 0) {
    LOGE("The wxWidgets controller returned invalid execution status");
    return INVALID;
  }

  return 0;
}

std::shared_ptr<wxwi::WxWidgetsIniter> Application::create_wx_initer()
{
  return std::make_shared<wxwi::WxWidgetsIniter>();
}

}  // namespace app
