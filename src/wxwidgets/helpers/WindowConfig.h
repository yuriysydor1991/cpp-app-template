#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WXWIDGETS_WINDOWCONFIG_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WXWIDGETS_WINDOWCONFIG_CLASS_H

#include <string>

namespace wxwi::helpers
{

/**
 * @brief Plain (wxWidgets independent) holder for the main window appearance.
 *
 * The configuration is intentionally free of any wxWidgets type so it can be
 * built and unit tested without the wxWidgets library being available. The
 * wxWidgets specific window code (WxMainFrame) only reads the values from here.
 */
class WindowConfig
{
 public:
  virtual ~WindowConfig() = default;

  /**
   * @brief Builds the default window configuration.
   *
   * @param app_name The application name used to build the window title.
   * @param app_version The application version appended to the window title.
   */
  WindowConfig(const std::string& app_name, const std::string& app_version);

  const std::string& title() const;
  const std::string& header_text() const;
  const std::string& explanation_text() const;

  int width() const;
  int height() const;
  int min_width() const;
  int min_height() const;

 private:
  std::string window_title;
  std::string header;
  std::string explanation;

  int window_width{500};
  int window_height{400};
  int window_min_width{400};
  int window_min_height{300};
};

}  // namespace wxwi::helpers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WXWIDGETS_WINDOWCONFIG_CLASS_H
