#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IFONTAWESOMESTYLE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IFONTAWESOMESTYLE_CLASS_H

#include <memory>
#include <string>

/**
 * @brief The Font Awesome Free icon set adaptor subsystem namespace.
 */
namespace fontawesome
{

/**
 * @brief A single style of the Font Awesome Free distribution.
 *
 * The Free distribution splits it's icons into styles, each one shipped as an
 * own svgs/ subdirectory of individual SVG files and as an own webfont file
 * carrying the very same icons as glyphs. Every descendant answers for one of
 * those styles, so the calling code names a style by an instance instead of an
 * enumeration value and gains a new style by a new descendant alone.
 */
class IFontAwesomeStyle
{
 public:
  using IFontAwesomeStylePtr = std::shared_ptr<IFontAwesomeStyle>;

  virtual ~IFontAwesomeStyle() = default;

  /**
   * @brief Gives the style name, which is also the name of it's svgs/
   * subdirectory inside the Font Awesome checkout.
   *
   * @return Returns the style name, the "solid" one for example.
   */
  virtual std::string name() const = 0;

  /**
   * @brief Gives the name of the webfonts/ file carrying the style icons as
   * the font glyphs.
   *
   * The file name follows no rule the style name would derive it by, hence the
   * separate accessor.
   *
   * @return Returns the webfont file name, the "fa-solid-900.woff2" one for
   * example.
   */
  virtual std::string webfontFileName() const = 0;
};

using IFontAwesomeStylePtr = IFontAwesomeStyle::IFontAwesomeStylePtr;

}  // namespace fontawesome

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IFONTAWESOMESTYLE_CLASS_H
