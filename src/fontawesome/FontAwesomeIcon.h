#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEICON_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEICON_CLASS_H

#include <memory>
#include <string>

#include "src/fontawesome/styles/IFontAwesomeStyle.h"

namespace fontawesome
{

/**
 * @brief A single icon of the Font Awesome Free distribution.
 *
 * Pairs an icon name with the style it belongs to and derives every name the
 * surrounding code asks the pair for: the SVG file name, the resource alias,
 * the checkout relative path and the absolute path of the very SVG file.
 */
class FontAwesomeIcon
{
 public:
  using FontAwesomeIconPtr = std::shared_ptr<FontAwesomeIcon>;

  virtual ~FontAwesomeIcon() = default;

  /**
   * @brief Constructs the icon of the given name and style.
   *
   * @param gstyle The style the icon belongs to.
   * @param gname The icon name with no style, path or extension parts, the
   * "folder-open" one for example.
   */
  FontAwesomeIcon(IFontAwesomeStylePtr gstyle, std::string gname);

  /**
   * @brief Gives the style the icon belongs to.
   */
  const IFontAwesomeStylePtr& style() const;

  /**
   * @brief Gives the plain icon name, the "folder-open" one for example.
   */
  const std::string& name() const;

  /**
   * @brief Gives the SVG file name of the icon.
   *
   * @return Returns the file name, the "folder-open.svg" one for example.
   */
  std::string fileName() const;

  /**
   * @brief Gives the alias every generated resource manifest keys the icon by.
   *
   * Both the .qrc and the .gresource.xml manifests the fontawesome enabler
   * writes carry this very alias, so it is the single name the compiled in
   * resource and the code below agree upon.
   *
   * @return Returns the alias, the "solid/folder-open.svg" one for example.
   */
  std::string alias() const;

  /**
   * @brief Gives the path of the icon SVG file relative to the Font Awesome
   * checkout root directory.
   *
   * @return Returns the relative path, the "svgs/solid/folder-open.svg" one
   * for example.
   */
  std::string relativePath() const;

  /**
   * @brief Gives the absolute path of the icon SVG file inside the Font
   * Awesome checkout the project has been configured with.
   *
   * @return Returns the absolute path of the SVG file.
   */
  std::string filePath() const;

  static FontAwesomeIconPtr create(IFontAwesomeStylePtr gstyle,
                                   std::string gname);

 private:
  /// @brief The Font Awesome checkout subdirectory holding the per style
  /// individual SVG icon files.
  inline static const std::string SVGS_DIRECTORY_NAME = "svgs";

  /// @brief The extension of every individual Font Awesome icon file.
  inline static const std::string SVG_EXTENSION = ".svg";

  IFontAwesomeStylePtr mstyle;
  std::string mname;
};

using FontAwesomeIconPtr = FontAwesomeIcon::FontAwesomeIconPtr;

}  // namespace fontawesome

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEICON_CLASS_H
