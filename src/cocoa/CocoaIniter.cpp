#include "src/cocoa/CocoaIniter.h"

#include <cassert>
#include <memory>

#include "src/app/IApplication.h"
#include "src/cocoa/CocoaLauncher.h"
#include "src/log/log.h"

namespace cocoa
{

int CocoaIniter::run(std::shared_ptr<app::ApplicationContext> nactx)
{
  assert(nactx != nullptr);

  if (nactx == nullptr) {
    LOGE("Invalid context pointer provided");
    return app::IApplication::INVALID;
  }

  actx = nactx;

  LOGD("Starting the Cocoa application");

  return launch(actx->argc, actx->argv);
}

int CocoaIniter::launch(int& argc, char**& argv)
{
  return run_cocoa_application(argc, argv);
}

}  // namespace cocoa
