#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEGRESOURCEPATH_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEGRESOURCEPATH_CLASS_H

#include <string>

#include "src/fontawesome/FontAwesomeIcon.h"
#include "src/fontawesome/resources/FontAwesomeResourcePath.h"
#include "src/fontawesome/resources/IFontAwesomeResourcePath.h"

namespace fontawesome
{

/**
 * @brief The locator of an icon embedded into the GLib GResource system.
 *
 * Resolves the icons of a .gresource.xml manifest the fontawesome enabler has
 * written, so a Gtkmm based branch of the template hands the resulting path
 * over to a Gtk::Image, a Gdk::Texture or a Gio::Resource lookup and nothing
 * else is needed.
 */
class FontAwesomeGResourcePath : public FontAwesomeResourcePath
{
 public:
  explicit FontAwesomeGResourcePath(std::string gprefix);

  /**
   * @brief Gives the "/<prefix>/<style>/<name>.svg" path the resource path
   * taking Gtk and Gio calls resolve the icon by.
   */
  std::string of(const FontAwesomeIconPtr& icon) const override;

  /**
   * @brief Gives the "resource:///<prefix>/<style>/<name>.svg" URI the Gio
   * file calls resolve the icon by.
   */
  std::string uriOf(const FontAwesomeIconPtr& icon) const override;

  /**
   * @brief Creates the locator for the prefix the generated .gresource.xml
   * manifests of this project use.
   */
  static IFontAwesomeResourcePathPtr create();

  static IFontAwesomeResourcePathPtr create(std::string gprefix);

 private:
  /// @brief The GResource URI scheme, whose authority part stays empty, hence
  /// the third slash coming from the leading one of the prefix.
  inline static const std::string RESOURCE_SCHEME = "resource://";
};

}  // namespace fontawesome

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEGRESOURCEPATH_CLASS_H
