#include "src/cocoa/CocoaController.h"

#include <cassert>
#include <memory>

#include "src/app/applications/IApplication.h"
#include "src/cocoa/CocoaLauncher.h"
#include "src/log/log.h"

namespace cocoa
{

int CocoaController::run(std::shared_ptr<app::ApplicationContext> nactx)
{
  assert(nactx != nullptr);

  if (nactx == nullptr) {
    LOGE("Invalid context pointer provided");
    return app::IApplication::INVALID;
  }

  actx = nactx;

  LOGD("Starting the Cocoa application");

  return launch(actx->get_argc(), actx->get_argv());
}

int CocoaController::launch(int& argc, char**& argv)
{
  return run_cocoa_application(argc, argv,
                               [ctx = actx]() { return ctx->get_stop(); });
}

}  // namespace cocoa
