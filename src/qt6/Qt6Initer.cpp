#include "src/qt6/Qt6Initer.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QString>

#include "src/app/IApplication.h"
#include "src/log/log.h"
#include "src/qt6/QMLRes.h"
#include "src/qtdbus/QtDBusController.h"
#include "src/qtdbus/SystemInformation.h"

namespace Qt6i
{

int Qt6Initer::run(std::shared_ptr<app::ApplicationContext> actx)
{
  using QMLRes = qmlpaths::QMLRes;

  assert(actx != nullptr);

  if (actx == nullptr) {
    LOGE("No valid application context pointer provided");
    return app::IApplication::INVALID;
  }

  QCoreApplication::setOrganizationName(
      QString::fromStdString(project_decls::PROJECT_NAME));

  QGuiApplication app(actx->argc, actx->argv);
  QQmlApplicationEngine engine;

  // Query the general system information over the system D-Bus (hostname1)
  // and publish it to QML as the "systemInfo" context property so the main
  // window may simply bind to it. An unreachable bus is non-fatal for the GUI:
  // the window still opens and surfaces the problem through systemInfo.error.
  qtdbusi::SystemInformation sysinfo;
  qtdbusi::QtDBusControllerPtr dbus = qtdbusi::QtDBusController::create();

  if (dbus == nullptr) {
    LOGW("System D-Bus is not reachable; system information stays empty");
    sysinfo.error = QStringLiteral("The system D-Bus bus is not reachable");
    sysinfo.notifyChanged();
  } else if (!dbus->run(sysinfo)) {
    LOGW("Failed to obtain the system information over D-Bus");
  }

  engine.rootContext()->setContextProperty(QStringLiteral("systemInfo"),
                                            &sysinfo);

  LOGI("Trying to load " << QMLRes::get_url_main().toStdString());

  engine.addImportPath(QMLRes::get_url_main_import());
  engine.load(QMLRes::get_url_main());

  if (engine.rootObjects().isEmpty()) {
    LOGE("Fail to initialize the Qt6 QML engine");
    return app::IApplication::INVALID;
  }

  return app.exec();
}

}  // namespace Qt6i
