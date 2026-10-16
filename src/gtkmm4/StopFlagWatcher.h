#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_STOPFLAGWATCHER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_STOPFLAGWATCHER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/gtkmm4/gtkmm4_includes.h"

namespace Gtkmm4i
{

/**
 * @brief Quits the given application main loop as soon as the OS signals
 * (Ctrl+C, kill and so on) raise the application context stop flag.
 *
 * The signal handlers are only allowed to raise the flag, so it is polled by a
 * main loop timer, which is removed together with the watcher.
 */
class StopFlagWatcher : public sigc::trackable
{
 public:
  virtual ~StopFlagWatcher() = default;
  StopFlagWatcher(std::shared_ptr<app::ApplicationContext> nactx,
                  Gio::Application& napp);

 private:
  bool quit_on_stop();

  inline static constexpr unsigned int poll_period_ms = 100;

  std::shared_ptr<app::ApplicationContext> actx;
  Gio::Application& gapp;
};

}  // namespace Gtkmm4i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_STOPFLAGWATCHER_CLASS_H
