#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WXMAINFRAME_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WXMAINFRAME_CLASS_H

#include "src/wxwidgets/helpers/WindowConfig.h"
#include "src/wxwidgets/wxwidgets_includes.h"

namespace wxwi::main_window
{

/**
 * @brief The default templated wxWidgets main window.
 *
 * Builds its appearance from the wxWidgets independent WindowConfig so the
 * shown texts, title and sizes stay testable in isolation.
 */
class WxMainFrame : public wxFrame
{
 public:
  explicit WxMainFrame(const helpers::WindowConfig& config);

 private:
  void build_widgets(const helpers::WindowConfig& config);
};

}  // namespace wxwi::main_window

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WXMAINFRAME_CLASS_H
