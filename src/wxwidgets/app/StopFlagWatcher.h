#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WX_STOPFLAGWATCHER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WX_STOPFLAGWATCHER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/wxwidgets/wxwidgets_includes.h"

namespace wxwi::app
{

/**
 * @brief Leaves the wxWidgets application main loop as soon as the OS signals
 * (Ctrl+C, kill and so on) raise the application context stop flag.
 *
 * The signal handlers are only allowed to raise the flag, so it is polled by
 * this timer, which the running application starts with the poll_period_ms
 * interval.
 */
class StopFlagWatcher : public wxTimer
{
 public:
  ~StopFlagWatcher() override = default;
  explicit StopFlagWatcher(std::shared_ptr<::app::ApplicationContext> nactx);

  void Notify() override;

  /// @brief The stop flag poll interval, in milliseconds.
  inline static constexpr int poll_period_ms = 100;

 private:
  std::shared_ptr<::app::ApplicationContext> actx;
};

}  // namespace wxwi::app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WX_STOPFLAGWATCHER_CLASS_H
