#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IGNOREDSIGNALSHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IGNOREDSIGNALSHANDLER_CLASS_H

#include <set>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/handlers/posix/PosixSignalsHandler.h"

namespace app
{

/**
 * @brief The handler of the OS signals the application deliberately ignores,
 * which is the SIGPIPE one of a write into a pipe or a socket nobody reads any
 * more.
 *
 * The class is the only one of the component which installs the SIG_IGN
 * disposition instead of a routine, so it touches no application context at
 * all and its ASignalsHandler::store_context override is an empty one.
 *
 * **The OS default reaction on the SIGPIPE signal terminates the process
 * silently**, which turns a disconnected peer into an unexplained application
 * death. Ignoring the signal makes the failing write return an EPIPE error
 * instead, so the calling code gets the chance to notice the broken connection
 * and to report it, which is why virtually every networking application
 * ignores the signal.
 *
 * The std::signal dispositions are the process wide ones, so a single alive
 * instance is expected.
 */
class IgnoredSignalsHandler : public PosixSignalsHandler
{
 public:
  /// @brief Releases the covered signals with the inherited
  /// ASignalsHandler::uninstall method.
  ~IgnoredSignalsHandler() override;
  IgnoredSignalsHandler() = default;

 protected:
  /// @brief Provides the OS signals numbers the application ignores. See the
  /// ASignalsHandler class.
  virtual const std::set<int>& get_handled_signals() override;

  /// @brief Provides the SIG_IGN value instead of a routine. See the
  /// ASignalsHandler class.
  virtual SignalDisposition get_signal_disposition() override;

  /// @brief Keeps nothing, since an ignored signal reaches no routine and
  /// needs no context at all. See the ASignalsHandler class.
  virtual void store_context(ApplicationContext* ctx) override;
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IGNOREDSIGNALSHANDLER_CLASS_H
