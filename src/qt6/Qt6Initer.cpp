#include "src/qt6/Qt6Initer.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>

#include "project-global-decls.h"
#include "src/app/IApplication.h"
#include "src/log/log.h"

namespace templateQt6app
{

int Qt6Initer::run(std::shared_ptr<app::ApplicationContext> actx)
{
  assert(actx != nullptr);

  if (actx == nullptr) {
    LOGE("No valid application context pointer provided");
    return app::IApplication::INVALID;
  }

  QCoreApplication::setOrganizationName(
      QString::fromStdString(project_decls::PROJECT_NAME));

  QGuiApplication app(actx->argc, actx->argv);
  QQmlApplicationEngine engine;

  engine.load(QUrl(main_qml_path));

  if (engine.rootObjects().isEmpty()) {
    LOGE("Fail to initialize the Qt6 QML engine");
    return app::IApplication::INVALID;
  }

  return app.exec();
}

}  // namespace templateQt6app
