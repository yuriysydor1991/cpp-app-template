#include "src/qt6/QMLRes.h"

#include <QString>

#include "project-global-decls.h"

namespace Qt6i::qmlpaths
{

const QString& QMLRes::get_url_main()
{
  static const QString main_url{
    QStringLiteral(":/")  
    + QString::fromStdString(project_decls::PROJECT_URI) 
    + QStringLiteral("/main/main.qml")
  };

  return main_url;
}

const QString& QMLRes::get_url_main_import()
{
  static const QString main_import_url{
    QStringLiteral(":/")  
    + QString::fromStdString(project_decls::PROJECT_URI)
  };

  return main_import_url;
}

}  // namespace Qt6i::qmlpaths
