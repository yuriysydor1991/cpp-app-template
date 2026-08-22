#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEGENERATEDICONS_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEGENERATEDICONS_CLASS_H

#include <string>
#include <vector>

namespace fontawesome
{

/**
 * @brief The icon names of the Font Awesome checkout the project has been
 * configured with.
 *
 * The implementation file is generated into the build directory by the
 * cmake/enablers/icons/template-project-fontawesome-index-generator.cmake
 * module out of the very checkout in use, so the complete icon set ends up
 * compiled into the binary and no directory ever gets scanned at the run time.
 */
class FontAwesomeGeneratedIcons
{
 public:
  using NamesList = std::vector<std::string>;

  /**
   * @brief Gives the plain names of every icon the given style ships.
   *
   * @param styleName The style name of interest, the "solid" one for example.
   *
   * @return Returns the sorted icon names, an empty list when the checkout
   * carries no icons of such a style.
   */
  static const NamesList& names(const std::string& styleName);
};

}  // namespace fontawesome

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FONTAWESOMEGENERATEDICONS_CLASS_H
