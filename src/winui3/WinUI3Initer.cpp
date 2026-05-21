#include "src/winui3/WinUI3Initer.h"

#include <cassert>
#include <memory>

#include "src/app/IApplication.h"
#include "src/log/log.h"
#include "src/winui3/WinUI3Launcher.h"

namespace winui3
{

int WinUI3Initer::run(std::shared_ptr<app::ApplicationContext> nactx)
{
  assert(nactx != nullptr);

  if (nactx == nullptr) {
    LOGE("Invalid context pointer provided");
    return app::IApplication::INVALID;
  }

  actx = nactx;

  LOGD("Starting the WinUI 3 application");

  return launch(actx->argc, actx->argv);
}

int WinUI3Initer::launch(int& argc, char**& argv)
{
  return run_winui_application(argc, argv);
}

}  // namespace winui3
