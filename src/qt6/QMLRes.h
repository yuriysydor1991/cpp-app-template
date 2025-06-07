#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_QMLRES_STRUCT_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_QMLRES_STRUCT_H

#include <QUrl>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace Qt6i::qmlpaths
{

/**
 * @brief The projects all resources paths holder.
 */
struct QMLRes
{
 public:
  virtual ~QMLRes() = default;
  QMLRes() = default;

  static const QUrl& get_url_main();

  static QUrl get_url_from(const char* const& resPath);

  inline static constexpr const char* const main_qml_path =
      "qrc:/ui/qml/main.qml";
  inline static constexpr const char* const the_logo_path =
      "qrc:/ui/resources/images/kytok.org.ua-logo.png";
};

}  // namespace Qt6i::qmlpaths

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_QMLRES_STRUCT_H
