#include "src/wxwidgets/WxWidgetsIniter.h"

#include <cassert>
#include <memory>

#include "src/app/IApplication.h"
#include "src/log/log.h"
#include "src/wxwidgets/WxLauncher.h"

namespace wxwi
{

int WxWidgetsIniter::run(std::shared_ptr<app::ApplicationContext> nactx)
{
  assert(nactx != nullptr);

  if (nactx == nullptr) {
    LOGE("Invalid context pointer provided");
    return app::IApplication::INVALID;
  }

  actx = nactx;

  LOGD("Starting the wxWidgets application");

  return launch(actx->argc, actx->argv);
}

int WxWidgetsIniter::launch(int& argc, char**& argv)
{
  return run_wx_application(argc, argv);
}

}  // namespace wxwi
