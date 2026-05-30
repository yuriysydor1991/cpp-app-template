#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3MAINWINDOW_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3MAINWINDOW_CLASS_H

#include "src/winui3/gl-area/GLTriangleArea.h"
#include "src/winui3/helpers/WindowConfig.h"
#include "src/winui3/winui3_includes.h"

namespace winui3::main_window
{

/**
 * @brief The default templated WinUI 3 main window.
 *
 * Builds a WinUI 3 Window and its content programmatically (no XAML file) from
 * the WinUI 3 independent WindowConfig, so the shown texts, title and sizes stay
 * testable in isolation. Replace build_content() with your own UI (or a real
 * XAML page) when starting development.
 */
class WinUI3MainWindow
{
 public:
  explicit WinUI3MainWindow(const helpers::WindowConfig& config);

  /// @brief The underlying WinUI 3 window (ref-counted, safe to outlive *this).
  winrt::Microsoft::UI::Xaml::Window window() const;

 private:
  void build_content(const helpers::WindowConfig& config);

  winrt::Microsoft::UI::Xaml::Window win{nullptr};
  gl_area::GLTriangleArea gl_canvas;
};

}  // namespace winui3::main_window

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3MAINWINDOW_CLASS_H
