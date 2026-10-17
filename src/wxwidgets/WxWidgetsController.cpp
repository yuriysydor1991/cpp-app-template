#include "src/wxwidgets/WxWidgetsController.h"

#include <cassert>
#include <memory>

#include "src/app/applications/IApplication.h"
#include "src/log/log.h"
#include "src/wxwidgets/WxLauncher.h"

namespace wxwi
{

int WxWidgetsController::run(std::shared_ptr<app::ApplicationContext> nactx)
{
  assert(nactx != nullptr);

  if (nactx == nullptr) {
    LOGE("Invalid context pointer provided");
    return app::IApplication::INVALID;
  }

  actx = nactx;

  LOGD("Starting the wxWidgets application");

  return launch(actx->get_argc(), actx->get_argv());
}

int WxWidgetsController::launch(int& argc, char**& argv)
{
  return run_wx_application(actx, argc, argv);
}

}  // namespace wxwi
