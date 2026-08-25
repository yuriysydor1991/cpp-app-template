#include "src/gtkmm4/GtkmmIniter.h"

#include <giomm/init.h>

#include <cassert>

#include "src/app/applications/IApplication.h"
#include "src/gdbus/GDBusController.h"
#include "src/gtkmm4/log/GtkLogBridge.h"
#include "src/log/log.h"

namespace Gtkmm4i
{

int GtkmmIniter::run(std::shared_ptr<app::ApplicationContext> nactx)
{
  // Every message the toolkit reports lands in the application log from here
  // on. It is taken over before anything of the toolkit is touched, so the
  // complaints of it's own start up are caught as well.
  gtklog::GtkLogBridge::install();

  assert(nactx != nullptr);

  if (nactx == nullptr) {
    LOGE("Invalid context pointer provided");
    return app::IApplication::INVALID;
  }

  // giomm/GLib must be initialized before any Gio::DBus usage. No GLib main
  // loop is run: the controller performs synchronous (blocking) property reads,
  // logs the obtained system information through the LOGI calls in the query
  // handler and returns. No GUI window is created.
  Gio::init();

  gdbusi::GDBusControllerPtr dbus = gdbusi::GDBusController::create();

  if (dbus == nullptr) {
    LOGE("Fail to create the system D-Bus controller");
    return app::IApplication::INVALID;
  }

  if (!dbus->run()) {
    LOGE("Failed to obtain the system information over D-Bus");
    return app::IApplication::INVALID;
  }

  return 0;
}

}  // namespace Gtkmm4i
