#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_COCOAMAINWINDOW_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_COCOAMAINWINDOW_CLASS_H

#include "src/cocoa/cocoa_includes.h"
#include "src/cocoa/helpers/WindowConfig.h"

namespace cocoa::main_window
{

/**
 * @brief The default templated macOS Cocoa main window.
 *
 * Builds an AppKit NSWindow and its content programmatically (no .xib/.nib file)
 * from the Cocoa independent WindowConfig, so the shown texts, title and sizes
 * stay testable in isolation. Replace build_content() with your own UI when
 * starting development. The held NSWindow is reference counted by ARC.
 */
class CocoaMainWindow
{
 public:
  explicit CocoaMainWindow(const helpers::WindowConfig& config);

  /// @brief The underlying AppKit window.
  NSWindow* window() const;

 private:
  void build_content(const helpers::WindowConfig& config);

  NSWindow* win{nil};
};

}  // namespace cocoa::main_window

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_COCOAMAINWINDOW_CLASS_H
