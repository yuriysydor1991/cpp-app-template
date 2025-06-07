#include "src/qt6/QMLRes.h"

#include <memory>

#include "src/app/ApplicationContext.h"

namespace Qt6i::qmlpaths
{

const QUrl& QMLRes::get_url_main()
{
  static const QUrl main_url = get_url_from(main_qml_path);

  return main_url;
}

inline QUrl QMLRes::get_url_from(const char* const& resPath)
{
  return QUrl{resPath};
}

}  // namespace Qt6i::qmlpaths
