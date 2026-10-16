#include "src/qt6/Qt6Controller.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QTimer>

#include "src/app/applications/IApplication.h"
#include "src/log/log.h"
#include "src/qt6/QMLRes.h"
#include "src/qt6/log/QtLogBridge.h"

namespace Qt6i
{

int Qt6Controller::run(std::shared_ptr<app::ApplicationContext> actx)
{
  using QMLRes = qmlpaths::QMLRes;

  // Every message the toolkit reports lands in the application log from here
  // on. It is taken over before anything of the toolkit is touched, so the
  // complaints of it's own start up are caught as well.
  qtlog::QtLogBridge::install();

  assert(actx != nullptr);

  if (actx == nullptr) {
    LOGE("No valid application context pointer provided");
    return app::IApplication::INVALID;
  }

  QCoreApplication::setOrganizationName(
      QString::fromStdString(project_decls::PROJECT_NAME));

  QApplication app(actx->get_argc(), actx->get_argv());
  QQmlApplicationEngine engine;

  LOGI("Trying to load " << QMLRes::get_url_main().toStdString());

  engine.addImportPath(QMLRes::get_url_main_import());
  engine.load(QMLRes::get_url_main());

  if (engine.rootObjects().isEmpty()) {
    LOGE("Fail to initialize the Qt6 QML engine");
    return app::IApplication::INVALID;
  }

  // The OS signals only raise the context stop flag, so the event loop polls
  // it and is left as soon as the flag is raised.
  QTimer stopPoller;
  QObject::connect(&stopPoller, &QTimer::timeout, &app, [&actx]() {
    if (actx->get_stop()) {
      LOGI("The stop flag is raised, leaving the Qt event loop");
      QCoreApplication::quit();
    }
  });
  stopPoller.start(stop_poll_interval_ms);

  return app.exec();
}

}  // namespace Qt6i
