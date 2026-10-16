#include "src/gtkmm4/StopFlagWatcher.h"

#include <cassert>
#include <utility>

#include "src/log/log.h"

namespace Gtkmm4i
{

StopFlagWatcher::StopFlagWatcher(std::shared_ptr<app::ApplicationContext> nactx,
                                 Gio::Application& napp)
    : actx{std::move(nactx)}, gapp{napp}
{
  assert(actx != nullptr);

  Glib::signal_timeout().connect(
      sigc::mem_fun(*this, &StopFlagWatcher::quit_on_stop), poll_period_ms);
}

bool StopFlagWatcher::quit_on_stop()
{
  if (!actx->get_stop()) {
    return true;
  }

  LOGI("The application stop is requested, quitting the main loop");

  gapp.quit();

  return false;
}

}  // namespace Gtkmm4i
