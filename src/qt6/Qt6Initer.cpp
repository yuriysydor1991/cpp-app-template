#include "src/qt6/Qt6Initer.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>

#include "project-global-decls.h"
#include "src/app/IApplication.h"
#include "src/log/log.h"

namespace templateQt6app
{

int Qt6Initer::run(int& argc, char**& argv)
{
  QCoreApplication::setOrganizationName(
      QString::fromStdString(project_decls::PROJECT_NAME));

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  engine.load(QUrl(main_qml_path));

  if (engine.rootObjects().isEmpty()) {
    LOGE("Fail to initialize the Qt6 QML engine");
    return app::IApplication::INVALID;
  }

  return app.exec();
}

}  // namespace templateQt6app
