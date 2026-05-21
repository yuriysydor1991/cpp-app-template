#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3_WINDOWCONFIG_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3_WINDOWCONFIG_CLASS_H

#include <string>

namespace winui3::helpers
{

/**
 * @brief Plain (WinUI 3 independent) holder for the main window appearance.
 *
 * The configuration is intentionally free of any WinUI 3 / C++/WinRT type so it
 * can be built and unit tested without the Windows App SDK being available. The
 * WinUI 3 specific window code (WinUI3MainWindow) only reads the values here.
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

}  // namespace winui3::helpers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3_WINDOWCONFIG_CLASS_H
