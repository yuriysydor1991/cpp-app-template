#include "src/wxwidgets/app/StopFlagWatcher.h"

#include <cassert>
#include <utility>

#include "src/log/log.h"

namespace wxwi::app
{

StopFlagWatcher::StopFlagWatcher(
    std::shared_ptr<::app::ApplicationContext> nactx)
    : actx{std::move(nactx)}
{
  assert(actx != nullptr);
}

void StopFlagWatcher::Notify()
{
  if (actx == nullptr || !actx->get_stop()) {
    return;
  }

  LOGI("The application stop is requested, leaving the main loop");

  Stop();

  // The console application base keeps the watcher usable by any wxWidgets
  // application, the GUI one and the console one alike.
  wxAppConsole* const running = wxAppConsole::GetInstance();

  if (running != nullptr) {
    running->ExitMainLoop();
  }
}

}  // namespace wxwi::app
