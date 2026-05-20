#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WXAPP_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WXAPP_CLASS_H

#include "src/wxwidgets/wxwidgets_includes.h"

namespace wxwi::app
{

/**
 * @brief The default wxWidgets application object.
 *
 * Creates and shows the main application frame on initialization.
 */
class WxApp : public wxApp
{
 public:
  bool OnInit() override;
};

}  // namespace wxwi::app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WXAPP_CLASS_H
