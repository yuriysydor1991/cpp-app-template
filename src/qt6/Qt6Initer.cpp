#include "src/qt6/Qt6Initer.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QString>

#include "src/app/applications/IApplication.h"
#include "src/log/log.h"
#include "src/qt6/QMLRes.h"
#include "src/qt6/gl-area/GLTriangleItem.h"

namespace Qt6i
{

namespace
{

/** @brief The QML module the C++ implemented items are exposed through. */
constexpr const char* GLAREA_URI = "glarea";
constexpr int GLAREA_VERSION_MAJOR = 1;
constexpr int GLAREA_VERSION_MINOR = 0;

}  // namespace

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

  QGuiApplication app(actx->get_argc(), actx->get_argv());

  // Every C++ implemented QML type has to be registered before the QML files
  // referencing it are loaded.
  qmlRegisterType<gl_area::GLTriangleItem>(
      GLAREA_URI, GLAREA_VERSION_MAJOR, GLAREA_VERSION_MINOR, "GLTriangleItem");

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
