#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEQTRESOURCEPATH_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEQTRESOURCEPATH_CLASS_H

#include <string>

#include "src/fontawesome/FontAwesomeIcon.h"
#include "src/fontawesome/resources/FontAwesomeResourcePath.h"
#include "src/fontawesome/resources/IFontAwesomeResourcePath.h"

namespace fontawesome
{

/**
 * @brief The locator of an icon embedded into the Qt resource system.
 *
 * Resolves the icons of a .qrc manifest the fontawesome enabler has written,
 * so a Qt based branch of the template hands the resulting path over to a
 * QIcon, a QPixmap or a QML Image source and nothing else is needed.
 */
class FontAwesomeQtResourcePath : public FontAwesomeResourcePath
{
 public:
  explicit FontAwesomeQtResourcePath(std::string gprefix);

  /**
   * @brief Gives the ":/<prefix>/<style>/<name>.svg" path a QIcon and the
   * other file name taking Qt calls resolve the icon by.
   */
  std::string of(const FontAwesomeIconPtr& icon) const override;

  /**
   * @brief Gives the "qrc:/<prefix>/<style>/<name>.svg" URL a QUrl and the QML
   * source properties resolve the icon by.
   */
  std::string uriOf(const FontAwesomeIconPtr& icon) const override;

  /**
   * @brief Creates the locator for the prefix the generated .qrc manifests of
   * this project use.
   */
  static IFontAwesomeResourcePathPtr create();

  static IFontAwesomeResourcePathPtr create(std::string gprefix);

 private:
  /// @brief The Qt resource system marks it's paths with a leading colon.
  inline static const std::string RESOURCE_MARK = ":";

  /// @brief The Qt resource system URL scheme.
  inline static const std::string RESOURCE_SCHEME = "qrc:";
};

}  // namespace fontawesome

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEQTRESOURCEPATH_CLASS_H
