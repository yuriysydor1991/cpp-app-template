#include "src/qt6/Qt6Initer.h"

#include <cassert>

#include <QCoreApplication>

#include "src/app/IApplication.h"
#include "src/log/log.h"
#include "src/qtdbus/QtDBusController.h"

namespace Qt6i
{

int Qt6Initer::run(std::shared_ptr<app::ApplicationContext> actx)
{
  assert(actx != nullptr);

  if (actx == nullptr) {
    LOGE("No valid application context pointer provided");
    return app::IApplication::INVALID;
  }

  // QtDBus needs a living QCoreApplication instance for its bus integration.
  // No event loop (app.exec()) is required: the controller performs synchronous
  // (blocking) property reads, logs the obtained system information through the
  // LOGI calls in the query handler and returns.
  QCoreApplication app(actx->argc, actx->argv);

  qtdbusi::QtDBusControllerPtr dbus = qtdbusi::QtDBusController::create();

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

}  // namespace Qt6i
