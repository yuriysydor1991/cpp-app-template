#include "src/qt6/Qt6Initer.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>

#include "src/app/applications/IApplication.h"
#include "src/log/log.h"
#include "src/qt6/QMLRes.h"
#include "src/qt6/log/QtLogBridge.h"

namespace Qt6i
{

int Qt6Initer::run(std::shared_ptr<app::ApplicationContext> actx)
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

  QGuiApplication app(actx->get_argc(), actx->get_argv());
  QQmlApplicationEngine engine;

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
