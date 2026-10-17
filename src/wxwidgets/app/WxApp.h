#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WXAPP_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WXAPP_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/wxwidgets/app/StopFlagWatcher.h"
#include "src/wxwidgets/wxwidgets_includes.h"

namespace wxwi::app
{

/**
 * @brief The default wxWidgets application object.
 *
 * Creates and shows the main application frame on initialization and leaves
 * the main loop once the application context stop flag is raised.
 */
class WxApp : public wxApp
{
 public:
  ~WxApp() override = default;
  explicit WxApp(std::shared_ptr<::app::ApplicationContext> nactx);

  bool OnInit() override;
  int OnExit() override;

 private:
  std::shared_ptr<::app::ApplicationContext> actx;

  /// @brief Leaves the main loop once the OS signals raise the stop flag.
  std::unique_ptr<StopFlagWatcher> stopWatcher;
};

}  // namespace wxwi::app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WXAPP_CLASS_H
