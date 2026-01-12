#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_QMLRES_STRUCT_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_QMLRES_STRUCT_H

#include <QString>

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

  static const QString& get_url_main();
  static const QString& get_url_main_import();
};

}  // namespace Qt6i::qmlpaths

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_QMLRES_STRUCT_H
